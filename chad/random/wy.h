#ifndef RANDOM_WY_H_
#define RANDOM_WY_H_

#include <stdint.h>

typedef uint64_t random_wy_t;

random_wy_t random_wy_init(uint32_t init);
uint32_t random_wy32(random_wy_t * randomp);
uint64_t random_wy64(random_wy_t * randomp);

#endif /* RANDOM_WY_H_ */
