#ifndef RANDOM_XOROSHIRO_H_
#define RANDOM_XOROSHIRO_H_

#include <terry.h>
#include "bits.h"

typedef struct { u64 a, b; } xoroshiro_t;

xoroshiro_t RANDOM_PREFIX(xoroshiro_init_raw)(u128 init);
u64 RANDOM_PREFIX(xoroshiro_next)(xoroshiro_t * randomp);

#define X xoroshiro
#define X_NEXT_WIDTH 64
#include "implements.h"

#endif /* RANDOM_XOROSHIRO_H_ */
