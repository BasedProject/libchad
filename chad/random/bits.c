#include "bits.h"

#include <string.h>

u128 RANDOM_PREFIX(init_block)(const char * buffer, size_t length)
{ u128 reg = 0, acc = 0;
  size_t i;
  for (i = 0; i < length/16; ++i)
  { memcpy(&reg, buffer + i * 16, 16);
    acc ^= reg;
  }
  reg = 0;
  memcpy(&reg, buffer + i * 16, length - i * 16);
  acc ^= reg;
  return acc;
}
