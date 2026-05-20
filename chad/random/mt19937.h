#ifndef RANDOM_MT19937_H
#define RANDOM_MT19937_H

#include <terry.h>
#include "bits.h"

#define MT19937_N 624

typedef struct {
    u32 mt[MT19937_N];
    int index;
} mt19937_t;

mt19937_t RANDOM_PREFIX(mt19937_init_raw)(u32 init);
u32 RANDOM_PREFIX(mt19937_next)(mt19937_t * randomp);

#define X mt19937
#include "implements.h"

#endif /* RANDOM_MT19937_H */
