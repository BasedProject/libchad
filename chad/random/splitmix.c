/* https://mit-license.org/ - Copyright 2025 wallstop */
#include "splitmix.h"

random_splitmix_t random_splitmix_init(uint64_t init) {
  return init;
}

uint32_t random_splitmix32(random_splitmix_t * randomp) {
  return random_splitmix64(randomp);
}

uint64_t random_splitmix64(random_splitmix_t * randomp) {
  random_splitmix_t random = *randomp;
  random += 0x9E3779B97F4A7C15ULL;
  *randomp = random;

  random = (random ^ (random >> 30)) * 0xBF58476D1CE4E5B9ULL;
  random = (random ^ (random >> 27)) * 0x94D049BB133111EBULL;
  random ^= random >> 31;

  return random;
}
