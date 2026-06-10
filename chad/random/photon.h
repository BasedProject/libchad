#ifndef RANDOM_PHOTON_H_
#define RANDOM_PHOTON_H_

#include <terry.h>
#include "bits.h"

#ifndef PHOTON_BLOCK_SIZE
#define PHOTON_BLOCK_SIZE 20
#endif

#ifndef PHOTON_SPIN_INCREMENT
#define PHOTON_SPIN_INCREMENT 111111U
#endif

typedef struct {
    u32 elements[PHOTON_BLOCK_SIZE];
    u32 a;
    u32 b;
    u32 c;
    s32 index;                  /* 0..PHOTON_BLOCK_SIZE */
    bool has_primed;
} photon_t;

photon_t RANDOM_PREFIX(photon_init_raw)(u128 init);
u32 RANDOM_PREFIX(photon_next)(photon_t * randomp);

#define X photon
#include "implements.h"

#endif /* RANDOM_PHOTON_H_ */
