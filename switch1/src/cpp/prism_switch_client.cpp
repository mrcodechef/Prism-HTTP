#include <iostream>
#include <arpa/inet.h>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "prism_switch.grpc.pb.h"

#include <prism_switch/prism_switch_client.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using prism::PrismSwitch;
using prism::PrismSwitchAddReq;
using prism::PrismSwitchChangeOwnerReq;
using prism::PrismSwitchDeleteReq;
using prism::PrismSwitchLockReq;
using prism::PrismSwitchReply;

class PrismSwitchClient {
public:
  PrismSwitchClient(std::shared_ptr<Channel> channel)
      : stub_(PrismSwitch::NewStub(channel))
  {
  }

  int
  Add(PrismSwitchAddReq &req)
  {
    ClientContext context;
    PrismSwitchReply reply;
    Status status = stub_->Add(&context, req, &reply);

    if (!status.ok()) {
      std::cerr << "message: " << status.error_message() << std::endl;
      std::cerr << "code: " << status.error_code() << std::endl;
      std::cerr << "details: " << status.error_details() << std::endl;
      return -1;
    }

    return reply.error();
  }

  int
  Delete(PrismSwitchDeleteReq &req)
  {
    ClientContext context;
    PrismSwitchReply reply;
    Status status = stub_->Delete(&context, req, &reply);

    if (!status.ok()) {
      std::cerr << "message: " << status.error_message() << std::endl;
      std::cerr << "code: " << status.error_code() << std::endl;
      std::cerr << "details: " << status.error_details() << std::endl;
      return -1;
    }

    return reply.error();
  }

  int
  ChangeOwner(PrismSwitchChangeOwnerReq &req)
  {
    ClientContext context;
    PrismSwitchReply reply;
    Status status = stub_->ChangeOwner(&context, req, &reply);

    if (!status.ok()) {
      std::cerr << "message: " << status.error_message() << std::endl;
      std::cerr << "code: " << status.error_code() << std::endl;
      std::cerr << "details: " << status.error_details() << std::endl;
      return -1;
    }

    return reply.error();
  }

  int
  Lock(PrismSwitchLockReq &req)
  {
    ClientContext context;
    PrismSwitchReply reply;
    Status status = stub_->Lock(&context, req, &reply);

    if (!status.ok()) {
      std::cerr << "message: " << status.error_message() << std::endl;
      std::cerr << "code: " << status.error_code() << std::endl;
      std::cerr << "details: " << status.error_details() << std::endl;
      return -1;
    }

    return reply.error();
  }

  int
  Unlock(PrismSwitchLockReq &req)
  {
    ClientContext context;
    PrismSwitchReply reply;
    Status status = stub_->Unlock(&context, req, &reply);

    if (!status.ok()) {
      std::cerr << "message: " << status.error_message() << std::endl;
      std::cerr << "code: " << status.error_code() << std::endl;
      std::cerr << "details: " << status.error_details() << std::endl;
      return -1;
    }

    return reply.error();
  }

private:
  std::unique_ptr<PrismSwitch::Stub> stub_;
};

struct prism_switch_client_s {
  PrismSwitchClient *c;
};

prism_switch_client_t *
prism_switch_client_create(const char *host)
{
  PrismSwitchClient *c = new PrismSwitchClient(
      grpc::CreateChannel(host, grpc::InsecureChannelCredentials()));

  prism_switch_client_t *client =
      (prism_switch_client_t *)malloc(sizeof(*client));
  if (client == NULL) {
    delete c;
  }

  client->c = c;

  return client;
}

void
prism_switch_client_destroy(prism_switch_client_t *client)
{
  delete client->c;
  free(client);
}

int
prism_switch_add(prism_switch_client_t *client,
                 struct prism_switch_add_req *req)
{
  PrismSwitchAddReq rpc_req;

  rpc_req.set_peer_addr(req->peer_addr);
  rpc_req.set_peer_port(req->peer_port);
  rpc_req.set_virtual_addr(req->virtual_addr);
  rpc_req.set_virtual_port(req->virtual_port);
  rpc_req.set_owner_addr(req->owner_addr);
  rpc_req.set_owner_port(req->owner_port);
  rpc_req.set_lock(req->lock);

  uint64_t mac;
  memcpy(&mac, req->owner_mac, 6);
  rpc_req.set_owner_mac(mac);

  return client->c->Add(rpc_req);
}

int
prism_switch_delete(prism_switch_client_t *client,
                    struct prism_switch_delete_req *req)
{
  PrismSwitchDeleteReq rpc_req;

  rpc_req.set_peer_addr(req->peer_addr);
  rpc_req.set_peer_port(req->peer_port);

  return client->c->Delete(rpc_req);
}

int
prism_switch_change_owner(prism_switch_client_t *client,
                          struct prism_switch_change_owner_req *req)
{
  PrismSwitchChangeOwnerReq rpc_req;

  rpc_req.set_peer_addr(req->peer_addr);
  rpc_req.set_peer_port(req->peer_port);
  rpc_req.set_owner_addr(req->owner_addr);
  rpc_req.set_owner_port(req->owner_port);
  rpc_req.set_unlock(req->unlock);

  uint64_t mac;
  memcpy(&mac, req->owner_mac, 6);
  rpc_req.set_owner_mac(mac);

  return client->c->ChangeOwner(rpc_req);
}

int
prism_switch_lock(prism_switch_client_t *client,
                  struct prism_switch_lock_req *req)
{
  PrismSwitchLockReq rpc_req;

  rpc_req.set_peer_addr(req->peer_addr);
  rpc_req.set_peer_port(req->peer_port);

  return client->c->Lock(rpc_req);
}

int
prism_switch_unlock(prism_switch_client_t *client,
                    struct prism_switch_lock_req *req)
{
  PrismSwitchLockReq rpc_req;

  rpc_req.set_peer_addr(req->peer_addr);
  rpc_req.set_peer_port(req->peer_port);

  return client->c->Unlock(rpc_req);
}
