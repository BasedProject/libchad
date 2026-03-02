/* https://mit-license.org/ - Copyright 2025 wallstop */
#include "photon.h"
#include "ro.h"

static
uint32_t mix32(uint64_t * mix) {
  *mix = (*mix ^ (*mix >> 33)) * 0xFF51AFD7ED558CCDULL;
  *mix = (*mix ^ (*mix >> 33)) * 0xC4CEB9FE1A85EC53ULL;
  *mix ^= (*mix >> 33);
  uint32_t result = (uint32_t)(*mix >> 32);
  *mix += 0x9E3779B97F4A7C15ULL;
  return result;
}

static inline
void normalize_index(random_photon_t * randomp) {
  if (randomp->index < 0 || randomp->index > RANDOM_PHOTON_BLOCK_SIZE) {
    randomp->index = RANDOM_PHOTON_BLOCK_SIZE;
  }
}

random_photon_t random_photon_init(uint64_t init_a, uint64_t init_b) {
  random_photon_t photon = {0};

  uint64_t mix = init_a ^ (init_b << 1) ^ 0x9E3779B97F4A7C15ULL;

  for (int i = 0; i < RANDOM_PHOTON_BLOCK_SIZE; ++i) {
    photon.elements[i] = mix32(&mix);
  }

  photon.a = mix32(&mix);
  photon.b = mix32(&mix);
  photon.c = mix32(&mix);

  photon.index = RANDOM_PHOTON_BLOCK_SIZE;
  photon.has_primed = 0;
  normalize_index(&photon);

  return photon;
}

static
void generate_block(random_photon_t * randomp) {
  uint32_t mix[4];
  int base_index = (int)(randomp->a & 15U);

  mix[0] = randomp->elements[base_index];
  mix[1] = randomp->elements[(base_index + 3) & 15];
  mix[2] = randomp->elements[(base_index + 6) & 15];
  mix[3] = randomp->elements[(base_index + 9) & 15];

  randomp->a += RANDOM_PHOTON_SPIN_INCREMENT;

  int k = 0, i, j;
  for (i = 0; i < 4; ++i) {
    randomp->b += randomp->a;
    randomp->c ^= randomp->a;
    mix[i] += random_rol32(randomp->b, 9);

    for (j = 0; j < 5; ++j) {
      randomp->elements[k] += random_rol32(mix[i], 25);
      randomp->elements[k] ^= randomp->c;
      mix[i] += randomp->elements[k];
      k++;
    }

    if (k >= 5
    &&  randomp->elements[k - 1] == randomp->elements[k - 2]
    &&  randomp->elements[k - 3] == randomp->elements[k - 4]) {
      randomp->elements[k - 1] +=  mix[i] ^ 81016U;
      randomp->elements[k - 2] +=  mix[i] ^ 297442265U;
      randomp->elements[k - 3] += (mix[i] ^ 5480U) | (mix[i] & 1U);
      randomp->elements[k - 4] +=  mix[i] ^ 19006808U;
      randomp->elements[k - 5] +=  mix[i];
    }
  }

  randomp->b += random_rol32(mix[0], 23);
  randomp->b ^= mix[1];
  randomp->c += random_rol32(mix[2], 13);
  randomp->c ^= mix[3];

  randomp->index = 0;
}

uint32_t random_photon32(random_photon_t * randomp) {
  if (!randomp->has_primed) {
    generate_block(randomp);
    randomp->has_primed = 1;
    randomp->index = RANDOM_PHOTON_BLOCK_SIZE;
  }

  if (randomp->index >= RANDOM_PHOTON_BLOCK_SIZE) {
    generate_block(randomp);
  }

  uint32_t value = randomp->elements[randomp->index];
  ++randomp->index;
  return value;
}
