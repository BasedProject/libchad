#ifndef RANDOM_SPLITMIX_H_
#define RANDOM_SPLITMIX_H_

#include <stdint.h>

typedef uint64_t random_splitmix_t;

random_splitmix_t random_splitmix_init(uint64_t init);
uint32_t random_splitmix32(random_splitmix_t * randomp);
uint64_t random_splitmix64(random_splitmix_t * randomp);

#endif /* RANDOM_SPLITMIX_H_ */
