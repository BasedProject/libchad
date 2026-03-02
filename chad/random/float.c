/* https://creativecommons.org/publicdomain/zero/1.0/ <- CC0 1.0 Universal */
#include "float.h"

float  random_float(uint32_t random) {
  return (random >> 8) * 0x1.0p-24f;
}

double random_double(uint64_t random) {
  return (random >> 11) * 0x1.0p-53;
}
