#ifndef RANDOM_GRAND_H_
#define RANDOM_GRAND_H_

/* DOES NOT RESPECT ALIGN_RANDOM AT ALL!
 *  GRAND THINKS HE'S A TOTAL LOSER!
 *
 * A bit much work to implement for probably no benefit,
 *   just use any other rng directly.
 */

#include <terry.h>
#include "bits.h"

#ifndef GRAND
#include "photon.h"                                              
#define GRAND photon
#define GRAND_WIDTH 32                                            
#endif                                                            

typedef RANDOM_CONCAT(GRAND,_t) grand_t;

/* DYNAMIC DISPATCH! */
extern RANDOM_CONCAT(u,GRAND_WIDTH) (*grand_next)(grand_t *);

extern grand_t grand_value[1];

static inline grand_t RANDOM_PREFIX(grand_init_raw)(u128 init)
{ return RANDOM_CONCAT(GRAND,_init_raw)(init); }

static inline grand_t RANDOM_PREFIX(grand_init)(const char * buffer, size_t length)
{ return RANDOM_PREFIX(grand_init_raw)(RANDOM_PREFIX(init_block)(buffer, length)); }

static inline RANDOM_CONCAT(u,GRAND_WIDTH) grand_next_real(grand_t * grand)
{ return RANDOM_CONCAT(GRAND,_next)(grand);
}

static inline RANDOM_CONCAT(u,GRAND_WIDTH) grand_next_init(grand_t * grand)
{ *grand = RANDOM_PREFIX(grand_init_raw)(0);
  grand_next = grand_next_real;
  return RANDOM_CONCAT(GRAND,_next)(grand);
}

#define grand() RANDOM_CONCAT(grand_u,GRAND_WIDTH)()
static inline u32 RANDOM_PREFIX(grand_u32)(void) {
  return grand_next(grand_value);
}

static inline u64 RANDOM_PREFIX(grand_u64)(void) {
  #if GRAND_WIDTH >= 64
  return grand_next(grand_value);
  #else                     
  u64 r = ((u64) grand_next(grand_value) <<  0)
        | ((u64) grand_next(grand_value) << 32);
  return r;
  #endif
}

static inline u128 RANDOM_PREFIX(grand_u128)(void) {
  #if GRAND_WIDTH >= 128
  return grand_next(grand_value);
  #elif GRAND_WIDTH >= 64
  u128 r = ((u128) grand_next(grand_value) <<  0)
         | ((u128) grand_next(grand_value) << 64);
  return r;                   
  #else                       
  u128 r = ((u128) grand_next(grand_value) <<  0)
         | ((u128) grand_next(grand_value) << 32)
         | ((u128) grand_next(grand_value) << 64)
         | ((u128) grand_next(grand_value) << 96);
  return r;
  #endif
}

static inline s32 RANDOM_PREFIX(grand_s32)(void) {
  return (s32)(grand_u32() - ((u32)1 << 31));
}

static inline s64 RANDOM_PREFIX(grand_s64)(void) {
  return (s64)(grand_u64() - ((u64)1 << 63));
}

static inline s128 RANDOM_PREFIX(grand_s128)(void) {
  return (s128)(grand_u128() - ((u128)1 << 127));
}

static inline s32 RANDOM_PREFIX(grand_i32)(void) {
  return grand_s32();
}

static inline s64 RANDOM_PREFIX(grand_i64)(void) {
  return grand_s64();
}

static inline s128 RANDOM_PREFIX(grand_i128)(void) {
  return grand_s128();
}

static inline f32 RANDOM_PREFIX(grand_f32)(void) {
  return (grand_u32() >> 8) * 0x1.0p-24f;
}

static inline f64 RANDOM_PREFIX(grand_f64)(void) {
  return (grand_u64() >> 11) * 0x1.0p-53;
}

static inline u64 RANDOM_PREFIX(grand_range_u64)(u64 low, u64 high) {
  u64 range = high - low + 1u;
  if (!range) return grand_u64();
  u64 sample = grand_u64();
  u128 product = (u128) sample * range;
  u64 low_word = (u64) product;
  if (low_word < range) {
    u64 threshold = -range % range;
    while (low_word < threshold) {
      sample   = grand_u64();
      product  = (u128) sample * range;
      low_word = (u64) product;
    }
  }
  return low + (u64) (product >> 64);
}

static inline i32 RANDOM_PREFIX(grand_range_i32)(i32 low, i32 high) {
  u32 range = (u32) (high - low) + 1u;
  if (!range) return (i32)grand_u32();
  u32 sample = grand_u32();
  u64 product = (u64) sample * range;
  u32 low_word = (u32) product;
  if (low_word < range) {
    u32 threshold = -range % range;
    while (low_word < threshold) {
      sample   = grand_u32();
      product  = (u64) sample * range;
      low_word = (u32) product;
    }
  }
  return low + (i32)(product >> 32);
}

static inline i64 RANDOM_PREFIX(grand_range_i64)(i64 low, i64 high) {
  u64 range = (u64) (high - low) + 1u;
  if (!range) return (i64)grand_u64();
  u64 sample = grand_u64();
  u128 product = (u128) sample * range;
  u64 low_word = (u64) product;
  if (low_word < range) {
    u64 threshold = -range % range;
    while (low_word < threshold) {
      sample   = grand_u64();
      product  = (u128) sample * range;
      low_word = (u64) product;
    }
  }
  return low + (i64)(product >> 64);
}

static inline f32 RANDOM_PREFIX(grand_range_f32)(f32 low, f32 high) {
  return low + grand_f32() * (high - low);
}

static inline f64 RANDOM_PREFIX(grand_range_f64)(f64 low, f64 high) {
  return low + grand_f64() * (high - low);
}

#endif /* RANDOM_GRAND_H_ */
