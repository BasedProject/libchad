/* https://mit-license.org/ - Copyright 2025 wallstop */
#include "pcg.h"
#include "rotate.h"

pcg_t RANDOM_PREFIX(pcg_init)(const char * buffer, size_t length)
{ return RANDOM_PREFIX(pcg_init_raw)(RANDOM_PREFIX(init_block)(buffer, length), RANDOM_PCG_PRIME);
}

pcg_t RANDOM_PREFIX(pcg_init_raw)(u64 init, u64 increment) {
  pcg_t pcg;
  pcg.a = init + increment;
  pcg.b = increment;
  (void) RANDOM_PREFIX(pcg_next)(&pcg);
  return pcg;
}

u32 RANDOM_PREFIX(pcg_next)(pcg_t * randomp) {
  uint64_t a = randomp->a;
  randomp->a = a * 6364136223846793005ULL + randomp->b;
  return random_ror32(((a >> 18) ^ a) >> 27, a >> 59);
}
