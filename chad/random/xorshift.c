/* https://mit-license.org/ - Copyright 2025 wallstop */
#include "xorshift.h"

static inline random_xorshift_t random_xorshift_normalize(random_xorshift_t random) {
  return random == 0 ? 2463534242 : random;
}

random_xorshift_t random_xorshift_init(uint32_t init) {
  return random_xorshift_normalize(init);
}

uint32_t random_xorshift32(random_xorshift_t * randomp) {
  random_xorshift_t random = *randomp;
  random    = random_xorshift_normalize(random);
  random   ^= random << 13;
  random   ^= random >> 17;
  random   ^= random << 5;
  *randomp  = random;
  return random;
}
