#ifndef RANDOM_LCG2_H_
#define RANDOM_LCG2_H_

#include <stdint.h>

typedef uint64_t random_lcg2_t;

random_lcg2_t random_lcg2_init(uint64_t init);
uint32_t random_lcg232(random_lcg2_t * randomp);
uint64_t random_lcg264(random_lcg2_t * randomp);

#endif /* RANDOM_LCG2_H_ */
