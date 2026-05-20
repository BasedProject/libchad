#ifndef RANDOM_XORSHIFT_H_
#define RANDOM_XORSHIFT_H_

#include <terry.h>
#include "bits.h"

typedef u32 xorshift_t;

u32 RANDOM_PREFIX(xorshift_next)(xorshift_t * randomp);
xorshift_t RANDOM_PREFIX(xorshift_init_raw)(u32 init);

#define X xorshift
#include "implements.h"

#endif /* RANDOM_XORSHIFT_H_ */
