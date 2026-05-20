#ifndef RANDOM_LCG_H_
#define RANDOM_LCG_H_

#include <terry.h>
#include "bits.h"

typedef u32 lcg_t;

u32 RANDOM_PREFIX(lcg_next)(lcg_t * randomp);
lcg_t RANDOM_PREFIX(lcg_init_raw)(u32 init);

#define X lcg
#include "implements.h"

#endif /* RANDOM_LCG_H_ */
