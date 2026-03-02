#ifndef RANDOM_PHOTON_H_
#define RANDOM_PHOTON_H_

#include <stdint.h>

#ifndef RANDOM_PHOTON_BLOCK_SIZE
#define RANDOM_PHOTON_BLOCK_SIZE 20
#endif

#ifndef RANDOM_PHOTON_SPIN_INCREMENT
#define RANDOM_PHOTON_SPIN_INCREMENT 111111U
#endif

typedef struct {
    uint32_t elements[RANDOM_PHOTON_BLOCK_SIZE];
    uint32_t a;
    uint32_t b;
    uint32_t c;
    int index;
    int has_primed;
} random_photon_t;

random_photon_t random_photon_init(uint64_t init_a, uint64_t init_b);
uint32_t random_photon32(random_photon_t * randomp);

#endif /* RANDOM_PHOTON_H_ */
