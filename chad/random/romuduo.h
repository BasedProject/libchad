#ifndef RANDOM_ROMUDUO_H_
#define RANDOM_ROMUDUO_H_

#include <terry.h>
#include "bits.h"

typedef u128 romuduo_t;

romuduo_t RANDOM_PREFIX(romuduo_init_raw)(u128 init);
u32 RANDOM_PREFIX(romuduo_next)(romuduo_t * randomp);

#define X romuduo
#include "implements.h"

#endif /* RANDOM_ROMUDUO_H_ */
