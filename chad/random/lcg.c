/* https://mit-license.org/ - Copyright 2025 wallstop */
#include "lcg.h"

lcg_t RANDOM_PREFIX(lcg_init_raw)(u32 init) {
  return (lcg_t) init;
}

u32 RANDOM_PREFIX(lcg_next)(lcg_t * randomp) {
  lcg_t random = *randomp;
  random   = random * 1664525 + 1013904223;
  *randomp = random;
  return random;
}
