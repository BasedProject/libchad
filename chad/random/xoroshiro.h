#ifndef RANDOM_XOROSHIRO_H_
#define RANDOM_XOROSHIRO_H_

#include <stdint.h>

typedef struct { uint64_t a, b; } random_xoroshiro_t;

random_xoroshiro_t random_xoroshiro_init(uint64_t init_a, uint64_t init_b);
uint32_t random_xoroshiro32(random_xoroshiro_t * randomp);
uint64_t random_xoroshiro64(random_xoroshiro_t * randomp);

#endif /* RANDOM_XOROSHIRO_H_ */
