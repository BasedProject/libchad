#ifndef RANDOM_LCG2_H_
#define RANDOM_LCG2_H_

#include <terry.h>
#include "bits.h"

typedef u64 lcg2_t;

lcg2_t RANDOM_PREFIX(lcg2_init_raw)(u64 init);
u64 RANDOM_PREFIX(lcg2_next)(lcg2_t * randomp);

#define X lcg2
#define X_NEXT_WIDTH 64
#include "implements.h"

#endif /* RANDOM_LCG_H_ */
