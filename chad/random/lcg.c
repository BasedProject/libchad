/* https://mit-license.org/ - Copyright 2025 wallstop */
#include "lcg.h"

random_lcg_t random_lcg_init(uint32_t init) {
  return (random_lcg_t) init;
}

uint32_t random_lcg32(random_lcg_t * randomp) {
  random_lcg_t random = *randomp;
  random   = random * 1664525 + 1013904223;
  *randomp = random;
  return random;
}
