#ifndef RANDOM_PCG_H_
#define RANDOM_PCG_H_

#include <stdint.h>

typedef struct {
  uint64_t a, b;
} random_pcg_t;

/* recommended for increment */
#define RANDOM_PCG_PRIME ((uint64_t)6554638469)

random_pcg_t random_pcg_init(uint64_t init, uint64_t increment);
uint32_t random_pcg32(random_pcg_t * randomp);

#endif /* RANDOM_PCG_H_ */
