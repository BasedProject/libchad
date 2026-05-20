/* https://mit-license.org/ - Copyright 2025 wallstop */
#include "romuduo.h"
#include "rotate.h"

static inline
void romuduo_normalize(romuduo_t * randomp) {
  if (*randomp == 0) {
    *randomp = ((u128) 0xD3833E804F4C574BUL << 64)
             | ((u128) 0x94D049BB133111EBUL);
  }
}

romuduo_t RANDOM_PREFIX(romuduo_init_raw)(u128 init) {
  romuduo_t romuduo;
  romuduo = (romuduo_t) init;
  romuduo_normalize(&romuduo);
  /* two steps to ensure strong initial randomness at edgecase of (1 0) */
  RANDOM_PREFIX(romuduo_next)(&romuduo);
  RANDOM_PREFIX(romuduo_next)(&romuduo);
  return romuduo;
}

u32 RANDOM_PREFIX(romuduo_next)(romuduo_t * randomp) {
  romuduo_normalize(randomp);
  u128 n = *randomp;
  *randomp = ((u128)(random_rol64(n, 27) + (n >> 64)) << 64)
           | ((u128)(15241094284759029579ULL * (u64)n));
  return n >> 64;
}
