#ifndef RANDOM_ROMUDUO_H_
#define RANDOM_ROMUDUO_H_

#include <stdint.h>

typedef struct { uint64_t a, b; } random_romuduo_t;

random_romuduo_t random_romuduo_init(uint64_t init_a, uint64_t init_b);
uint32_t random_romuduo32(random_romuduo_t * randomp);

#endif /* RANDOM_ROMUDUO_H_ */
