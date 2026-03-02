#ifndef RANDOM_MT19937_H
#define RANDOM_MT19937_H

#include <stdint.h>

#define MT19937_N 624

typedef struct {
    uint32_t mt[MT19937_N];
    int index;
} random_mt19937_t;

random_mt19937_t random_mt19937_init(uint32_t initial);
uint32_t random_mt1993732(random_mt19937_t * randomp);

#endif /* RANDOM_MT19937_H */
