#pragma once

#include <stdint.h>

struct prism_switch_client_s;
typedef struct prism_switch_client_s prism_switch_client_t;

struct prism_switch_add_req {
  uint32_t peer_addr;
  uint16_t peer_port;
  uint32_t virtual_addr;
  uint16_t virtual_port;
  uint32_t owner_addr;
  uint16_t owner_port;
  uint8_t *owner_mac;
  bool lock;
};

struct prism_switch_change_owner_req {
  uint32_t peer_addr;
  uint16_t peer_port;
  uint32_t owner_addr;
  uint16_t owner_port;
  uint8_t *owner_mac;
  bool unlock;
};

struct prism_switch_delete_req {
  uint32_t peer_addr;
  uint16_t peer_port;
};

struct prism_switch_lock_req {
  uint32_t peer_addr;
  uint16_t peer_port;
};

extern prism_switch_client_t *prism_switch_client_create(const char *host);
extern void prism_switch_client_destroy(prism_switch_client_t *client);
extern int prism_switch_add(prism_switch_client_t *client,
                            struct prism_switch_add_req *req);
extern int prism_switch_delete(prism_switch_client_t *client,
                               struct prism_switch_delete_req *req);
extern int prism_switch_change_owner(prism_switch_client_t *client,
                                     struct prism_switch_change_owner_req *req);
extern int prism_switch_lock(prism_switch_client_t *client,
                             struct prism_switch_lock_req *req);
extern int prism_switch_unlock(prism_switch_client_t *client,
                               struct prism_switch_lock_req *req);
