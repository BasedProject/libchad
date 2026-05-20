#ifndef RANDOM_PCG_H_
#define RANDOM_PCG_H_

#include <terry.h>
#include "bits.h"

typedef struct {
  u64 a, b;
} pcg_t;

/* recommended for pcg_t.b prime increment */
#define RANDOM_PCG_PRIME ((uint64_t)6554638469)

/* nongeneric interface */
pcg_t RANDOM_PREFIX(pcg_init)(const char * buffer, size_t length);
/* --- */
pcg_t RANDOM_PREFIX(pcg_init_raw)(u64 init, u64 increment);
u32 RANDOM_PREFIX(pcg_next)(pcg_t * randomp);

/* uses the above for increment... */
#define X pcg
#define X_PROVES_RULES           /* due to init_raw not being uN */
#include "implements.h"

#endif /* RANDOM_PCG_H_ */
