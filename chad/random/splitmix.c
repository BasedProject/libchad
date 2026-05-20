/* https://mit-license.org/ - Copyright 2025 wallstop */
#include "splitmix.h"

splitmix_t RANDOM_PREFIX(splitmix_init_raw)(u64 init) {
  return (splitmix_t) init;
}

u64 RANDOM_PREFIX(splitmix_next)(splitmix_t * randomp) {
  splitmix_t random = *randomp;
  random += 0x9E3779B97F4A7C15ULL;
  *randomp = random;
                           
  random = (random ^ (random >> 30)) * 0xBF58476D1CE4E5B9ULL;
  random = (random ^ (random >> 27)) * 0x94D049BB133111EBULL;
  random ^= random >> 31;

  return random;      
}
