/* https://mit-license.org/ - Copyright 2025 wallstop */
#include "xorshift.h"

static inline xorshift_t xorshift_normalize(xorshift_t random) {
  return random == 0 ? 2463534242 : random;
}

xorshift_t RANDOM_PREFIX(xorshift_init_raw)(u32 init) {
  return xorshift_normalize((xorshift_t) init);
}

u32 RANDOM_PREFIX(xorshift_next)(xorshift_t * randomp) {
  xorshift_t random = *randomp;
  random    = xorshift_normalize(random);
  random   ^= random << 13;
  random   ^= random >> 17;
  random   ^= random << 5;
  *randomp  = random;
  return random;
}
