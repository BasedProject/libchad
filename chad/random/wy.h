#ifndef RANDOM_WY_H_
#define RANDOM_WY_H_

#include <terry.h>
#include "bits.h"

typedef u64 wy_t;

wy_t RANDOM_PREFIX(wy_init_raw)(u64 init);
u64 RANDOM_PREFIX(wy_next)(wy_t * randomp);

#define X wy
#define X_NEXT_WIDTH 64
#include "implements.h"

#endif /* RANDOM_WY_H_ */
