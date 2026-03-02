#ifndef RANDOM_XORSHIFT_H_
#define RANDOM_XORSHIFT_H_

#include <stdint.h>

typedef uint32_t random_xorshift_t;

/* random_xorshift32_t xorrand32[1] = {xorshift32_init(initial)}; */
random_xorshift_t random_xorshift_init(uint32_t init);
uint32_t random_xorshift32(random_xorshift_t * randomp);

#endif /* RANDOM_XORSHIFT_H_ */
