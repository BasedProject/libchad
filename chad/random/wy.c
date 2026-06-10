#include "wy.h"

static inline
void multiply_64(u64 x, u64 y, u64 * high, u64 * low) {
    u64 x0 = (u32) x;
    u64 x1 = x >> 32;
    u64 y0 = (u32) y;
    u64 y1 = y >> 32;

    u64 p11 = x1 * y1;
    u64 p01 = x0 * y1;
    u64 p10 = x1 * y0;
    u64 p00 = x0 * y0;

    u64 middle = p10 + (p00 >> 32) + (u32) p01;

    *low = (middle << 32) | (u32) p00;
    *high = p11 + (middle >> 32) + (p01 >> 32);
}

static inline
u64 mum(u64 x, u64 y) {
    u64 high, low;
    multiply_64(x, y, &high, &low);
    return high ^ low;
}

wy_t RANDOM_PREFIX(wy_init_raw)(u64 init) {
  wy_t wy = init;
  (void) RANDOM_PREFIX(wy_next)(&wy);
  return wy;
}

u64 RANDOM_PREFIX(wy_next)(wy_t * randomp) {
  const u64 a = 0xa0761d6478bd642fULL, b = 0xe7037ed1a0b428dbULL;
  wy_t wy = *randomp;
  *randomp += a;
  return mum(wy ^ b, wy);
}
