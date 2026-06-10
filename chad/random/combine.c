/* https://creativecommons.org/publicdomain/zero/1.0/ <- CC0 1.0 Universal */
#include "combine.h"
uint64_t random_combine(uint32_t low, uint32_t high) {
  return low + ((uint64_t)high << 32);
}
