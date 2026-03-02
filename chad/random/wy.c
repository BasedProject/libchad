#include "wy.h"

static inline
void multiply_64(uint64_t x, uint64_t y, uint64_t * high, uint64_t * low) {
    uint64_t x0 = (uint32_t) x;
    uint64_t x1 = x >> 32;
    uint64_t y0 = (uint32_t) y;
    uint64_t y1 = y >> 32;

    uint64_t p11 = x1 * y1;
    uint64_t p01 = x0 * y1;
    uint64_t p10 = x1 * y0;
    uint64_t p00 = x0 * y0;

    uint64_t middle = p10 + (p00 >> 32) + (uint32_t) p01;

    *low = (middle << 32) | (uint32_t) p00;
    *high = p11 + (middle >> 32) + (p01 >> 32);
}

static inline
uint64_t mum(uint64_t x, uint64_t y) {
    uint64_t high, low;
    multiply_64(x, y, &high, &low);
    return high ^ low;
}

random_wy_t random_wy_init(uint32_t init) {
  random_wy_t wy = init;
  (void) random_wy64(&wy);
  return wy;
}

uint32_t random_wy32(random_wy_t * randomp) {
 return random_wy64(randomp);
}

uint64_t random_wy64(random_wy_t * randomp) {
  const uint64_t a = 0xa0761d6478bd642fULL, b = 0xe7037ed1a0b428dbULL;
  random_wy_t wy = *randomp;
  *randomp += a;
  return mum(wy ^ b, wy);
}
