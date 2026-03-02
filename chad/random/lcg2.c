#include "lcg2.h"

random_lcg2_t random_lcg2_init(uint64_t init) {
  return (random_lcg2_t) init;
}

uint32_t random_lcg232(random_lcg2_t * randomp) {
  return random_lcg264(randomp);
}

uint64_t random_lcg264(random_lcg2_t * randomp) {
  random_lcg2_t random = *randomp;
  random   = random * 2862933555777941757 + 3037000493;
  *randomp = random;
  return random;
}
