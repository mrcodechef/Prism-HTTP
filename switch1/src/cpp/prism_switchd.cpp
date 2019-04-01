#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <sys/poll.h>
#include <arpa/inet.h>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>

#include <prism_switch/prism_switch.h>
#include "prism_switch.grpc.pb.h"
#include "bcc_vale_bpf_native.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

using prism::PrismSwitch;
using prism::PrismSwitchAddReq;
using prism::PrismSwitchChangeOwnerReq;
using prism::PrismSwitchDeleteReq;
using prism::PrismSwitchLockReq;
using prism::PrismSwitchReply;

using ebpf::BPFHashTable;
using ebpf::StatusTuple;

class PrismSwitchImpl final : public PrismSwitch::Service {

private:
  ebpf::BPF *bpf;

  void
  print_add_req(const PrismSwitchAddReq *request)
  {
    uint8_t mac[6];
    uint64_t owner_mac = request->owner_mac();

    memcpy(mac, &owner_mac, 6);
    D("Add(peer: 0x%x:%u, virtual: 0x%x:%u, owner: 0x%x:%u mac "
      "%02x:%02x:%02x:%02x:%02x:%02x lock: %s)",
      ntohl(request->peer_addr()), ntohs((uint16_t)request->peer_port()),
      ntohl(request->virtual_addr()), ntohs((uint16_t)request->virtual_port()),
      ntohl(request->owner_addr()), ntohs((uint16_t)request->owner_port()),
      mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
      request->lock() ? "true" : "false");
  }

  void
  print_delete_req(const PrismSwitchDeleteReq *request)
  {
    D("Delete(peer: 0x%x:%u)", ntohl(request->peer_addr()),
      ntohs((uint16_t)request->peer_port()));
  }

  void
  print_change_owner_req(const PrismSwitchChangeOwnerReq *request)
  {
    uint8_t mac[6];
    uint64_t owner_mac = request->owner_mac();

    memcpy(mac, &owner_mac, 6);
    D("ChangeOwner(peer: 0x%x:%u, owner: 0x%x:%u mac "
      "%02x:%02x:%02x:%02x:%02x:%02x unlock: %s)",
      ntohl(request->peer_addr()), ntohs((uint16_t)request->peer_port()),
      ntohl(request->owner_addr()), ntohs((uint16_t)request->owner_port()),
      mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
      request->unlock() ? "true" : "false");
  }

  void
  print_lock_req(const PrismSwitchLockReq *request)
  {
    D("Lock(peer: 0x%x:%u)", ntohl(request->peer_addr()),
      ntohs((uint16_t)request->peer_port()));
  }

  void
  print_unlock_req(const PrismSwitchLockReq *request)
  {
    D("Unlock(peer: 0x%x:%u)", ntohl(request->peer_addr()),
      ntohs((uint16_t)request->peer_port()));
  }

public:
  explicit PrismSwitchImpl(ebpf::BPF *bpf) { this->bpf = bpf; }

  Status
  Add(ServerContext *context, const PrismSwitchAddReq *request,
      PrismSwitchReply *response) override
  {
    auto prism = bpf->get_hash_table<prism_key_t, prism_value_t>("prism");

#ifdef DEBUG
    print_add_req(request);
#endif

    prism_key_t key = {0};
    key.addr = request->peer_addr();
    key.port = request->peer_port();

    prism_value_t val = {0};
    val.virtual_addr = request->virtual_addr();
    val.virtual_port = request->virtual_port();
    val.owner_addr = request->owner_addr();
    val.owner_port = request->owner_port();
    val.locked = request->lock() ? 1 : 0;

    uint64_t mac = request->owner_mac();
    memcpy(val.owner_mac, &mac, 6);

    auto status = prism.update_value(key, val);
    if (status.code() == -1) {
      response->set_error(errno);
      return ::grpc::Status::CANCELLED;
    }

    response->set_error(0);

    return ::grpc::Status::OK;
  }

  Status
  Delete(ServerContext *context, const PrismSwitchDeleteReq *request,
         PrismSwitchReply *response) override
  {
    auto prism = bpf->get_hash_table<prism_key_t, prism_value_t>("prism");

#ifdef DEBUG
    print_delete_req(request);
#endif

    prism_key_t key = {0};
    key.addr = request->peer_addr();
    key.port = request->peer_port();

    auto status = prism.remove_value(key);
    if (status.code() == -1) {
      response->set_error(errno);
      return ::grpc::Status::CANCELLED;
    }

    response->set_error(0);

    return ::grpc::Status::OK;
  }

  Status
  ChangeOwner(ServerContext *context, const PrismSwitchChangeOwnerReq *request,
              PrismSwitchReply *response) override
  {
    auto prism = bpf->get_hash_table<prism_key_t, prism_value_t>("prism");

#ifdef DEBUG
    print_change_owner_req(request);
#endif

    prism_key_t key = {0};
    key.addr = request->peer_addr();
    key.port = request->peer_port();

    prism_value_t val = {0};

    auto status = prism.get_value(key, val);
    if (status.code() == -1) {
      response->set_error(errno);
      perror("get value");
      return ::grpc::Status::CANCELLED;
    }

    val.owner_addr = request->owner_addr();
    val.owner_port = request->owner_port();
    val.locked = request->unlock() ? 0 : 1;

    uint64_t mac = request->owner_mac();
    memcpy(val.owner_mac, &mac, 6);

    status = prism.update_value(key, val);
    if (status.code() == -1) {
      response->set_error(errno);
      return ::grpc::Status::CANCELLED;
    }

    response->set_error(0);

    return ::grpc::Status::OK;
  }

  Status
  Lock(ServerContext *context, const PrismSwitchLockReq *request,
       PrismSwitchReply *response) override
  {
    auto prism = bpf->get_hash_table<prism_key_t, prism_value_t>("prism");

#ifdef DEBUG
    print_lock_req(request);
#endif

    prism_key_t key = {0};
    prism_value_t val = {0};
    key.addr = request->peer_addr();
    key.port = request->peer_port();

    auto status = prism.get_value(key, val);
    if (status.code() == -1) {
      response->set_error(errno);
      return ::grpc::Status::CANCELLED;
    }

    if (val.locked == 1) {
      response->set_error(EBUSY);
      return ::grpc::Status::CANCELLED;
    }

    val.locked = 1;

    status = prism.update_value(key, val);
    if (status.code() == -1) {
      response->set_error(errno);
      return ::grpc::Status::CANCELLED;
    }

    response->set_error(0);

    return ::grpc::Status::OK;
  }

  Status
  Unlock(ServerContext *context, const PrismSwitchLockReq *request,
         PrismSwitchReply *response) override
  {
    auto prism = bpf->get_hash_table<prism_key_t, prism_value_t>("prism");

#ifdef DEBUG
    print_unlock_req(request);
#endif

    prism_key_t key = {0};
    prism_value_t val = {0};
    key.addr = request->peer_addr();
    key.port = request->peer_port();

    auto status = prism.get_value(key, val);
    if (status.code() == -1) {
      response->set_error(errno);
      return ::grpc::Status::CANCELLED;
    }

    if (val.locked == 0) {
      response->set_error(EEXIST);
      return ::grpc::Status::CANCELLED;
    }

    val.locked = 0;

    status = prism.update_value(key, val);
    if (status.code() == -1) {
      response->set_error(errno);
      return ::grpc::Status::CANCELLED;
    }

    response->set_error(0);

    return ::grpc::Status::OK;
  }
};

static struct {
  char *vale_name;
  char *address;
  char *include_path;
  char *bpf_src;
} g_conf;

static void
usage(char *prog_name)
{
  std::cerr
      << "Usage: " << prog_name
      << " -s <vale_name> -I <include path> -f <bpf source> -a <address:port> "
      << std::endl;
}

static int
parse_options(int argc, char **argv)
{
  int opt;

  g_conf.vale_name = NULL;
  g_conf.address = NULL;
  g_conf.include_path = NULL;

  while ((opt = getopt(argc, argv, "f:s:I:a:")) != -1) {
    switch (opt) {
    case 'f':
      g_conf.bpf_src = strdup(optarg);
      break;
    case 's':
      g_conf.vale_name = strdup(optarg);
      break;
    case 'I':
      g_conf.include_path = strdup(optarg);
      break;
    case 'a':
      g_conf.address = strdup(optarg);
      break;
    default:
      usage(argv[0]);
      return EINVAL;
    }
  }

  if (g_conf.vale_name == NULL || g_conf.vale_name == NULL ||
      g_conf.include_path == NULL) {
    usage(argv[0]);
    return EINVAL;
  }

  return 0;
}

static bool end = false;

#define TRACE_PIPE "/sys/kernel/debug/tracing/trace_pipe"
static void *
poll_tracing_pipe(void *arg)
{
  int fd = open(TRACE_PIPE, O_RDONLY);
  if (fd < 0) {
    std::cout << "Failed to open trace pipe" << std::endl;
    return NULL;
  }

  struct pollfd pfd;
  pfd.fd = fd;
  pfd.events = POLLIN;

  int error;
  char data[0xFFFF];
  ssize_t rlen;
  while (!end) {
    memset(data, 0, 0xFFFF);

    error = poll(&pfd, 1, 1);
    if (error == 0) {
      continue;
    } else if (error < 0) {
      perror("poll");
      break;
    }

    if (pfd.revents & POLLIN) {
      rlen = read(fd, data, 0xFFFF);
      if (rlen > 0) {
        std::cout << data;
        std::cout.flush();
      }
    }
  }

  return NULL;
}

int
main(int argc, char **argv)
{
  int error;

  error = parse_options(argc, argv);
  if (error) {
    return EXIT_FAILURE;
  }

  ebpf::VALE_BPF vale;
  std::string include_opt = "-I" + std::string(g_conf.include_path);
  std::vector<std::string> cflags = {include_opt, "-O3"};

  std::ifstream t(g_conf.bpf_src);
  std::stringstream prog;
  prog << t.rdbuf();

  auto status = vale.init(prog.str(), cflags);
  if (status.code() == -1) {
    std::cerr << status.msg() << std::endl;
    return EXIT_FAILURE;
  }

  std::string vale_name = std::string(g_conf.vale_name);
  if (vale_name.back() != ':') {
    vale_name += ":";
  }

  status = vale.attach_vale_bpf(vale_name, "vale_lookup");
  if (status.code() == -1) {
    std::cerr << status.msg() << std::endl;
    return EXIT_FAILURE;
  }

  pthread_t trace_thread;
  pthread_create(&trace_thread, NULL, poll_tracing_pipe, NULL);

  PrismSwitchImpl service(&vale);
  ServerBuilder builder;
  builder.AddListeningPort(g_conf.address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << g_conf.address << std::endl;
  server->Wait();
  pthread_join(trace_thread, NULL);

  return 0;
}
