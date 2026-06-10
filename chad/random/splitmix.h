#ifndef RANDOM_SPLITMIX_H_
#define RANDOM_SPLITMIX_H_

#include <terry.h>
#include "bits.h"

typedef u64 splitmix_t;

splitmix_t RANDOM_PREFIX(splitmix_init_raw)(u64 init);
u64 RANDOM_PREFIX(splitmix_next)(splitmix_t * randomp);

#define X splitmix
#define X_NEXT_WIDTH 64
#include "implements.h"

#endif /* RANDOM_SPLITMIX_H_ */
