/* https://mit-license.org/ - Copyright 2025 wallstop */
#include "xoroshiro.h"
#include "rotate.h"

static inline
void xoroshiro_normalize(xoroshiro_t * randomp) {
  if ((randomp->a | randomp->b) == 0) {
    randomp->a = 0x9E3779B97F4A7C15ULL;
    randomp->b = 0xD1B54A32D192ED03ULL;
  }
}
xoroshiro_t RANDOM_PREFIX(xoroshiro_init_raw)(u128 init) {
  xoroshiro_t xoroshiro;
  xoroshiro.a = (init >> 64);
  xoroshiro.b = init;
  xoroshiro_normalize(&xoroshiro);
  /* two steps to ensure strong initial randomness */
  /* [0..1] ~= seed when 0 */
  (void) xoroshiro_next(&xoroshiro);
  (void) xoroshiro_next(&xoroshiro);
  /* [2] = extremely poor (2*1025) when (N 0) */
  (void) xoroshiro_next(&xoroshiro);
  return xoroshiro;
}

u64 RANDOM_PREFIX(xoroshiro_next)(xoroshiro_t * randomp) {
  u64 a, b, sum;
  xoroshiro_normalize(randomp);
  a             = randomp->a;
  b             = randomp->b;
  sum           = a + b;
  b            ^= a;
  randomp->a    = random_rol64(a, 24) ^ b ^ (b << 16);
  randomp->b    = random_rol64(b, 37);
  return sum;
}
