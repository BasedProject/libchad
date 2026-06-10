#include "lcg2.h"

lcg2_t RANDOM_PREFIX(lcg2_init_raw)(u64 init) {
  lcg2_t lcg2 = init;
  (void) RANDOM_PREFIX(lcg2_next)(&lcg2);
  return lcg2;
}

u64 RANDOM_PREFIX(lcg2_next)(lcg2_t * randomp) {
  lcg2_t random = *randomp;
  random   = random * 2862933555777941757 + 3037000493;
  *randomp = random;
  return random;
}
