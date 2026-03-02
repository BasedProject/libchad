/* https://mit-license.org/ - Copyright 2025 wallstop */
#include "pcg.h"
#include "ro.h"

random_pcg_t random_pcg_init(uint64_t init, uint64_t increment) {
  random_pcg_t pcg;
  pcg.a = init + increment;
  pcg.b = increment;
  (void) random_pcg32(&pcg);
  return pcg;
}

uint32_t random_pcg32(random_pcg_t * randomp) {
  uint64_t a = randomp->a;
  randomp->a = a * 6364136223846793005ULL + randomp->b;
  return random_ror32(((a >> 18) ^ a) >> 27, a >> 59);
}
