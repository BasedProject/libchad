/* https://mit-license.org/ - Copyright 2025 wallstop */
#include "romuduo.h"
#include "ro.h"

static inline
void random_romuduo_normalize(random_romuduo_t * randomp) {
  if ((randomp->a | randomp->b) == 0)
  {
    randomp->a = 0xD3833E804F4C574BUL;
    randomp->b = 0x94D049BB133111EBUL;
  }
}

random_romuduo_t random_romuduo_init(uint64_t init_a, uint64_t init_b) {
  random_romuduo_t romuduo;
  romuduo.a = init_a;
  romuduo.b = init_b;
  random_romuduo_normalize(&romuduo);
  /* first step to ensure strong initial randomness at initial point */
  random_romuduo32(&romuduo);
  /* second step to ensure stronger initial randomness at edgecase of (1 0) */
  random_romuduo32(&romuduo);
  return romuduo;
}

uint32_t random_romuduo32(random_romuduo_t * randomp) {
  random_romuduo_normalize(randomp);
  uint64_t a = randomp->a, b = randomp->b;
  randomp->a = 15241094284759029579UL * b;
  randomp->b = random_rol64(b, 27) + a;
  return a;
}
