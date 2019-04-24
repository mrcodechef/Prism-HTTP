#include <math.h>
#include <netinet/ip.h>
#include <sys/resource.h>

#include <phttp.h>
#include <extern/tlse.h>
#include <leveldb/db.h>
#include <leveldb/slice.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/md5.h>

#include "common.h"

static leveldb::DB *db;
static struct phttp_args global_args;
static std::string proxy_addr;
static uint16_t proxy_port;
static std::string next_server_addr;
static uint16_t next_server_port;
static uint32_t nworkers;

static thread_local struct phttp_args thread_args;
static thread_local http_server_socket_t hss;
static thread_local http_handoff_server_socket_t hhss;
static thread_local http_server_handoff_data_t *conn_pool;
static thread_local http_server_handoff_data_t *next_server;
static thread_local struct global_config gconf;
static thread_local uint32_t rr_factor = 0;
static thread_local uint32_t nconnection;

static int
base64_encode(const char *message, size_t len, char **buf) {
  BIO *bio, *b64;
  FILE *stream;
  int enc_size = 4 * ceil((double)len / 3);
  *buf = (char *)malloc(enc_size + 1);
  memset(*buf, 0, enc_size + 1);

  stream = fmemopen(*buf, enc_size + 1, "w");
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_new_fp(stream, BIO_NOCLOSE);
  bio = BIO_push(b64, bio);
  BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
  BIO_write(bio, message, strlen(message));
  BIO_flush(bio);
  BIO_free_all(bio);
  fclose(stream);

  return 0;
}

static int
base16_encode(const char *message, size_t len, char **buf)
{
  *buf = (char *)malloc(len * 2 + 1);
  assert(*buf != NULL);

  memset(*buf, 0, len * 2 + 1);

  char *cursor = *buf;
  for (size_t i = 0; i < len; i++) {
    cursor += sprintf(cursor, "%02x", message[i] & 0xff);
  }

  return 0;
}

static int
after_get_res(struct http_response *res)
{
  free(res->headers[0].val);
  return 0;
}

static int
kvs_backend_request_handler(struct http_request *req, struct http_response *res,
                            bool imported)
{
  int error;

  if (!imported) {
    res->status = 600;
    res->reason = "Handoff";
    res->handoff_data = conn_pool + rr_factor;
    if (++rr_factor == nconnection) {
      rr_factor = 0;
    }
    return 0;
  }

  char *b16_md5hash;
  char md5hash[MD5_DIGEST_LENGTH];
  leveldb::Status s;
  if (strncmp("GET", req->method, 3) == 0) {
    std::string val;

    s = db->Get(leveldb::ReadOptions(),
                leveldb::Slice(req->path, req->path_len),
                &val);
    if (s.IsNotFound()) {
      res->status = 404;
      res->reason = "Not Found";
      return 0;
    }

    if (!s.ok()) {
      res->status = 500;
      res->reason = "LevelDB GET Failed\n";
      return 0;
    }

    if (membuf_avail(&res->body_mem) < val.size()) {
      printf("Warning: Memory growing occured\n");
      membuf_grow(&res->body_mem, val.size() - membuf_avail(&res->body_mem));
    }

    memcpy(res->body_mem.begin, val.c_str(), val.size());
    membuf_consume(&res->body_mem, val.size());

    /*
    MD5((unsigned char *)res->body_mem.begin, membuf_used(&res->body_mem), (unsigned char *)md5hash);
    error = base16_encode(md5hash, MD5_DIGEST_LENGTH, &b16_md5hash);
    assert(error == 0);

    error = http_response_add_header(res, "ETag", 4,
        b16_md5hash, strlen(b16_md5hash));
    assert(error == 0);
    */

    res->status = 200;
    res->reason = "OK";
    // res->after_res = after_get_res;

    return 0;
  }

  leveldb::WriteOptions write_options;

  if (strncmp("PUT", req->method, 3) == 0) {
    if (req->body_len == 0) {
      res->status = 400;
      res->reason = "PUT need to have body\n";
      return 0;
    }

    write_options.sync = true;

    s = db->Put(write_options,
                leveldb::Slice(req->path, req->path_len),
                leveldb::Slice(req->body, req->body_len));
    if (!s.ok()) {
      res->status = 500;
      res->reason = "LevelDB PUT Failed\n";
      return 0;
    }

    if (next_server != NULL) {
      res->status = 600;
      res->reason = "Handoff";
      res->handoff_data = next_server;
      return 0;
    }

    /*
    MD5((unsigned char *)req->body, req->body_len, (unsigned char *)md5hash);
    error = base16_encode(md5hash, MD5_DIGEST_LENGTH, &b16_md5hash);
    assert(error == 0);

    error = http_response_add_header(res, "ETag", 4,
        b16_md5hash, strlen(b16_md5hash));
    assert(error == 0);
    */

    res->status = 200;
    res->reason = "OK";

    return 0;
  }

  if (strncmp("DELETE", req->method, 6) == 0) {
    write_options.sync = true;

    s = db->Delete(leveldb::WriteOptions(),
        leveldb::Slice(req->path, req->path_len));
    if (!s.ok()) {
      res->status = 500;
      res->reason = "LevelDB DELETE Failed\n";
      return 0;
    }

    error = http_response_add_header(res, "Connection", 10, "close", 5);
    assert(error == 0);

    res->status = 204;
    res->reason = "NoContent\n";

    return 0;
  }

  res->status = 405;
  res->reason = "Method Not Allowed\n";

  return 0;
}

#define CONN_POOL_SIZE 1
static int
start_connect_to_proxy(uv_loop_t *loop, std::string proxy_addr,
                       uint16_t proxy_port, uint32_t workerid)
{
  int error;

  nconnection = CONN_POOL_SIZE;
  conn_pool = (http_server_handoff_data_t *)calloc(sizeof(conn_pool[0]),
                                                   CONN_POOL_SIZE);
  assert(conn_pool != NULL);

  for (uint32_t i = 0; i < CONN_POOL_SIZE; i++) {
    conn_pool[i].addr = inet_addr(proxy_addr.c_str());
    conn_pool[i].port = htons(proxy_port + workerid);
    error = start_connect(loop, conn_pool + i);
    assert(error == 0);
  }

  return 0;
}

static int
start_connect_to_next_server(uv_loop_t *loop, std::string next_addr,
                             uint16_t next_port, uint32_t workerid)
{
  int error;

  uint32_t addr = inet_addr(next_addr.c_str());
  if (addr == 0) {
    next_server = NULL;
    return 0;
  }

  next_server = (http_server_handoff_data_t *)malloc(sizeof(*next_server));
  assert(next_server != NULL);

  next_server->addr = addr;
  next_server->port = htons(next_port + workerid);
  error = start_connect(loop, next_server);
  assert(error == 0);

  return 0;
}

static void
set_kvs_backend_args(argparse::ArgumentParser *parser)
{
  parser->addArgument({"--proxy-addr"}, "KVS proxy server IPv4 address");
  parser->addArgument({"--proxy-port"}, "KVS proxy server server TCP port");
  parser->addArgument({"--next-server-addr"}, "The next server address of replicate chain");
  parser->addArgument({"--next-server-port"}, "The next server port of replicate chain");
  parser->addArgument({"--nworkers"}, "Number of workers");
}

void *
worker_main(void *args)
{
  int error;
  uint64_t id = (uint64_t)args;
  uv_loop_t *loop;

  thread_args = global_args;

  loop = (uv_loop_t *)malloc(sizeof(*loop));
  assert(loop != NULL);

  uv_loop_init(loop);

  tweak_phttp_args(&thread_args, id);

  hss.request_handler = kvs_backend_request_handler;

#if HOPROTO == 2
  init_all_conf(loop, &thread_args, &hss, &hhss, &gconf);
#elif HOPROTO == 1 || HOPROTO == 3
  init_all_conf(&thread_args, &hss, &hhss, &gconf);
#endif

  loop->data = &gconf;

  error = phttp_server_init(loop, &hss);
  assert(error == 0);

  error = phttp_handoff_server_init(loop, &hhss);
  assert(error == 0);

  error = start_connect_to_proxy(loop, proxy_addr, proxy_port, id);
  assert(error == 0);

  error = start_connect_to_next_server(loop, next_server_addr,
      next_server_port, id);
  assert(error == 0);

  error = init_signal_handling(loop);
  assert(error == 0);

  make_dummy_work(loop);

  printf("Starting event loop... using libuv version %s\n",
         uv_version_string());
  uv_run(loop, UV_RUN_DEFAULT);

  if (hss.tls != NULL) {
    tls_destroy_context(hss.tls);
  }

  prism_switch_client_destroy(gconf.sw_client);
  free(loop);

  return NULL;
}

int
main(int argc, char **argv)
{
  int error;

  argparse::ArgumentParser parser(
      "phttp-kvs-backend", "Simple KVS application (backend)", "MIT");
  phttp_argparse_set_all_args(&parser);
  set_kvs_backend_args(&parser);

  auto args = parser.parseArgs(argc, argv);
  phttp_argparse_parse_all(&args, &global_args);
  proxy_addr = args.get<std::string>("proxy-addr");
  proxy_port = args.get<uint16_t>("proxy-port");
  next_server_addr = args.get<std::string>("next-server-addr");
  next_server_port = args.get<uint16_t>("next-server-port");
  nworkers = args.get<uint32_t>("nworkers");

  struct rlimit lim;
  lim.rlim_cur = 10000;
  lim.rlim_max = 10000;
  error = setrlimit(RLIMIT_NOFILE, &lim);
  assert(error == 0);

  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "./testdb", &db);
  assert(status.ok());

  /*
   * Main
   */
  pthread_t *workers = (pthread_t *)calloc(nworkers, sizeof(workers[0]));
  assert(workers != NULL);

  for (uint32_t i = 0; i < nworkers; i++) {
    error = pthread_create(workers + i, NULL, worker_main, (void *)i);
    assert(error == 0);
  }

  for (uint32_t i = 0; i < nworkers; i++) {
    error = pthread_join(workers[i], NULL);
    assert(error == 0);
  }

  free(workers);

  return 0;
}
