/* https://mit-license.org/ - Copyright 2025 wallstop */
#include "photon.h"
#include "rotate.h"

static
u32 mix32(u64 * mix) {
  *mix = (*mix ^ (*mix >> 33)) * 0xFF51AFD7ED558CCDULL;
  *mix = (*mix ^ (*mix >> 33)) * 0xC4CEB9FE1A85EC53ULL;
  *mix ^= (*mix >> 33);
  u32 result = (u32)(*mix >> 32);
  *mix += 0x9E3779B97F4A7C15ULL;
  return result;
}

static inline
void normalize_index(photon_t * randomp) {
  if (randomp->index < 0 || randomp->index > PHOTON_BLOCK_SIZE) {
    randomp->index = PHOTON_BLOCK_SIZE;
  }
}

photon_t RANDOM_PREFIX(photon_init_raw)(u128 init) {
  photon_t photon = {0};

  u64 mix = ((u64)init) ^ ((u64)(init >> 64) << 1) ^ 0x9E3779B97F4A7C15ULL;

  for (int i = 0; i < PHOTON_BLOCK_SIZE; ++i) {
    photon.elements[i] = mix32(&mix);
  }

  photon.a = mix32(&mix);
  photon.b = mix32(&mix);
  photon.c = mix32(&mix);

  photon.index = PHOTON_BLOCK_SIZE;
  photon.has_primed = 0;
  normalize_index(&photon);

  return photon;
}

static
void generate_block(photon_t * randomp) {
  u32 mix[4];
  int base_index = (int)(randomp->a & 15U);

  mix[0] = randomp->elements[base_index];
  mix[1] = randomp->elements[(base_index + 3) & 15];
  mix[2] = randomp->elements[(base_index + 6) & 15];
  mix[3] = randomp->elements[(base_index + 9) & 15];

  randomp->a += PHOTON_SPIN_INCREMENT;

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

u32 RANDOM_PREFIX(photon_next)(photon_t * randomp) {
  if (!randomp->has_primed) {
    generate_block(randomp);
    randomp->has_primed = 1;
    randomp->index = PHOTON_BLOCK_SIZE;
  }

  if (randomp->index >= PHOTON_BLOCK_SIZE) {
    generate_block(randomp);
  }

  u32 value = randomp->elements[randomp->index];
  ++randomp->index;
  return value;
}
