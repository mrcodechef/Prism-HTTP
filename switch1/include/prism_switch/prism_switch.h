#pragma once

typedef struct {
  uint32_t addr;
  uint32_t port;
} prism_key_t;

typedef struct {
  uint32_t virtual_addr;
  uint16_t virtual_port;
  uint32_t owner_addr;
  uint16_t owner_port;
  uint8_t owner_mac[6];
  uint8_t locked;
  uint8_t _pad;
} prism_value_t;

struct l2_key {
  uint8_t dst[6];
} __attribute__((packed));

typedef struct l2_key l2_key_t;
