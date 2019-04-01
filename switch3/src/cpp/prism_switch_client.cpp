#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>
#include <sys/socket.h>
#include <sys/poll.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <prism_switch/prism_switch.h>
#include <prism_switch/prism_switch_client.h>

struct prism_switch_client_s {
  int sock;
  pthread_mutex_t mutex;
};

static std::vector<std::string>
split(std::string str, char del)
{
  int first = 0;
  int last = str.find_first_of(del);

  std::vector<std::string> result;

  while ((size_t)first < str.size()) {
    std::string subStr(str, first, last - first);

    result.push_back(subStr);

    first = last + 1;
    last = str.find_first_of(del, first);

    if ((size_t)last == std::string::npos) {
      last = str.size();
    }
  }

  return result;
}

prism_switch_client_t *
prism_switch_client_create(const char *host)
{
  int sock, error;
  auto spl_host = split(host, ':');

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1) {
    return NULL;
  }

  struct sockaddr_in conn_addr;
  conn_addr.sin_family = AF_INET;
  conn_addr.sin_addr.s_addr = inet_addr(spl_host[0].c_str());
  conn_addr.sin_port = htons((uint16_t)atoi(spl_host[1].c_str()));

  error = connect(sock, (struct sockaddr *)&conn_addr, sizeof(conn_addr));
  if (error) {
    close(sock);
    return NULL;
  }

  prism_switch_client_t *client =
      (prism_switch_client_t *)malloc(sizeof(*client));
  if (client == NULL) {
    close(sock);
    return NULL;
  }

  client->sock = sock;
  pthread_mutex_init(&client->mutex, NULL);

  return client;
}

void
prism_switch_client_destroy(prism_switch_client_t *client)
{
  close(client->sock);
  free(client);
}

static int
wait_response(int sock, psw_req_base_t *req, size_t req_size)
{
  int error, ret, retry_count = 0;
  struct pollfd pfd;
  ssize_t sent_size, recv_size;

  psw_req_base_t *res = (psw_req_base_t *)malloc(req_size);
  assert(res != NULL);

  pfd.fd = sock;
  pfd.events = POLLIN;
  pfd.revents = 0;

  while (retry_count < 10) {
    sent_size = send(sock, (void *)req, req_size, 0);
    assert((size_t)sent_size == req_size);

    error = poll(&pfd, 1, 50);

    if (error == 0) {
      retry_count++;
      continue;
    }

    if (error == 1) {
      if (pfd.revents & POLLIN) {
        recv_size = recv(sock, (void *)res, req_size, 0);
        if (recv_size < 0) {
          perror("recv");
          exit(EXIT_FAILURE);
        }
        assert((size_t)recv_size == req_size);
        break;
      }
    }

    free(res);
    return -errno;
  }

  if (retry_count == 4) {
    fprintf(stderr, "Couldn't get response for ADD request from switch\n");
    free(res);
    return -ENETUNREACH;
  }

  ret = (int)-res->status;
  free(res);

  return ret;
}

int
prism_switch_add(prism_switch_client_t *client,
                 struct prism_switch_add_req *req)
{
  int ret;
  psw_add_req_t add_req = {0};

  add_req.type = PSW_REQ_ADD;
  add_req.status = 0;
  add_req.peer_addr = req->peer_addr;
  add_req.peer_port = req->peer_port;
  add_req.virtual_addr = req->virtual_addr;
  add_req.virtual_port = req->virtual_port;
  add_req.owner_addr = req->owner_addr;
  add_req.owner_port = req->owner_port;
  memcpy(add_req.owner_mac, req->owner_mac, 6);
  add_req.lock = req->lock ? 1 : 0;

  pthread_mutex_lock(&client->mutex);
  ret =
      wait_response(client->sock, (psw_req_base_t *)&add_req, sizeof(add_req));
  pthread_mutex_unlock(&client->mutex);

  return ret;
}

int
prism_switch_delete(prism_switch_client_t *client,
                    struct prism_switch_delete_req *req)
{
  int ret;
  psw_delete_req_t del_req = {0};

  del_req.type = PSW_REQ_DELETE;
  del_req.status = 0;
  del_req.peer_addr = req->peer_addr;
  del_req.peer_port = req->peer_port;

  pthread_mutex_lock(&client->mutex);
  ret =
      wait_response(client->sock, (psw_req_base_t *)&del_req, sizeof(del_req));
  pthread_mutex_unlock(&client->mutex);

  return ret;
}

int
prism_switch_change_owner(prism_switch_client_t *client,
                          struct prism_switch_change_owner_req *req)
{
  int ret;
  psw_chown_req_t chown_req = {0};

  chown_req.type = PSW_REQ_CHOWN;
  chown_req.status = 0;
  chown_req.peer_addr = req->peer_addr;
  chown_req.peer_port = req->peer_port;
  chown_req.owner_addr = req->owner_addr;
  chown_req.owner_port = req->owner_port;
  memcpy(chown_req.owner_mac, req->owner_mac, 6);
  chown_req.unlock = req->unlock ? 1 : 0;

  pthread_mutex_lock(&client->mutex);
  ret = wait_response(client->sock, (psw_req_base_t *)&chown_req,
                      sizeof(chown_req));
  pthread_mutex_unlock(&client->mutex);

  return ret;
}

int
prism_switch_lock(prism_switch_client_t *client,
                  struct prism_switch_lock_req *req)
{
  int ret;
  psw_lock_req_t lock_req = {0};

  lock_req.type = PSW_REQ_LOCK;
  lock_req.status = 0;
  lock_req.peer_addr = req->peer_addr;
  lock_req.peer_port = req->peer_port;

  pthread_mutex_lock(&client->mutex);
  ret = wait_response(client->sock, (psw_req_base_t *)&lock_req,
                      sizeof(lock_req));
  pthread_mutex_unlock(&client->mutex);

  return ret;
}

int
prism_switch_unlock(prism_switch_client_t *client,
                    struct prism_switch_lock_req *req)
{
  int ret;
  psw_lock_req_t unlock_req = {0};

  unlock_req.type = PSW_REQ_UNLOCK;
  unlock_req.status = 0;
  unlock_req.peer_addr = req->peer_addr;
  unlock_req.peer_port = req->peer_port;

  pthread_mutex_lock(&client->mutex);
  ret = wait_response(client->sock, (psw_req_base_t *)&unlock_req,
                      sizeof(unlock_req));
  pthread_mutex_unlock(&client->mutex);

  return ret;
}
