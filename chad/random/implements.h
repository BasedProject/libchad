/* Don't include this directly ever.
    This is an internal automation header.
     - Sig. The Cyberpolice
*/

/* X_NEXT_WIDTH sets the minimum size of each next. local to each next, implicit to =32 */
/* ALIGN_RANDOM sets the minimum size of every call. implementation time global */
/* X_PROVES_RULES lets the init function be defined otherwise. Interface is the same. */

#ifndef X_PROVES_RULES
static inline
RANDOM_CONCAT(X,_t) RANDOM_PREFIX(RANDOM_CONCAT(X,_init))(const char * buffer, size_t length) {
  return RANDOM_PREFIX(RANDOM_CONCAT(X,_init_raw))(RANDOM_PREFIX(init_block)(buffer, length));
}
#endif

#if X_NEXT_WIDTH == 64
static inline u32 RANDOM_PREFIX(RANDOM_CONCAT(X,_u32))(RANDOM_CONCAT(X,_t) * randomp) {
  u32 r = (u64) RANDOM_PREFIX(RANDOM_CONCAT(X,_next))(randomp);
  return r;
}

static inline u64 RANDOM_PREFIX(RANDOM_CONCAT(X,_u64))(RANDOM_CONCAT(X,_t) * randomp) {
  u64 r = (u64) RANDOM_PREFIX(RANDOM_CONCAT(X,_next))(randomp);
  #if ALIGN_RANDOM >= 128
  (void) RANDOM_PREFIX(RANDOM_CONCAT(X,_next))(randomp);
  #endif
  return r;
}

static inline u128 RANDOM_PREFIX(RANDOM_CONCAT(X,_u128))(RANDOM_CONCAT(X,_t) * randomp) {
  u128 r = (u128) RANDOM_PREFIX(RANDOM_CONCAT(X,_next))(randomp) <<  0
         | (u128) RANDOM_PREFIX(RANDOM_CONCAT(X,_next))(randomp) << 64;
  return r;
}
#else  /* we assume by default 32 */
static inline u32 RANDOM_PREFIX(RANDOM_CONCAT(X,_u32))(RANDOM_CONCAT(X,_t) * randomp) {
  u32 r = (u32) RANDOM_PREFIX(RANDOM_CONCAT(X,_next))(randomp);
  #if ALIGN_RANDOM >= 64
  (void) RANDOM_PREFIX(RANDOM_CONCAT(X,_next))(randomp);
  #endif
  return r;
}                               
                                
static inline u64 RANDOM_PREFIX(RANDOM_CONCAT(X,_u64))(RANDOM_CONCAT(X,_t) * randomp) {
  u64 r = (u64) RANDOM_PREFIX(RANDOM_CONCAT(X,_next))(randomp) <<  0
        | (u64) RANDOM_PREFIX(RANDOM_CONCAT(X,_next))(randomp) << 32;
  #if ALIGN_RANDOM >= 128
  (void) RANDOM_PREFIX(RANDOM_CONCAT(X,_next))(randomp);
  (void) RANDOM_PREFIX(RANDOM_CONCAT(X,_next))(randomp);
  #endif
  return r;
}                                
                                 
static inline u128 RANDOM_PREFIX(RANDOM_CONCAT(X,_u128))(RANDOM_CONCAT(X,_t) * randomp) {
  u128 r = (u128) RANDOM_PREFIX(RANDOM_CONCAT(X,_next))(randomp) <<  0
         | (u128) RANDOM_PREFIX(RANDOM_CONCAT(X,_next))(randomp) << 32
         | (u128) RANDOM_PREFIX(RANDOM_CONCAT(X,_next))(randomp) << 64
         | (u128) RANDOM_PREFIX(RANDOM_CONCAT(X,_next))(randomp) << 96;
  return r;
}                               
#endif

static inline s32 RANDOM_PREFIX(RANDOM_CONCAT(X,_s32))(RANDOM_CONCAT(X,_t) * randomp) {
  return (s32)(RANDOM_PREFIX(RANDOM_CONCAT(X,_u32))(randomp) - ((u32)1 << 31));
}

static inline s64 RANDOM_PREFIX(RANDOM_CONCAT(X,_s64))(RANDOM_CONCAT(X,_t) * randomp) {
  return (s64)(RANDOM_PREFIX(RANDOM_CONCAT(X,_u64))(randomp) - ((u64)1 << 63));
}                                
                                 
static inline s128 RANDOM_PREFIX(RANDOM_CONCAT(X,_s128))(RANDOM_CONCAT(X,_t) * randomp) {
  return (s128)(RANDOM_PREFIX(RANDOM_CONCAT(X,_u128))(randomp) - ((u128)1 << 127));
}                               

static inline s32 RANDOM_PREFIX(RANDOM_CONCAT(X,_i32))(RANDOM_CONCAT(X,_t) * randomp) {
  return RANDOM_PREFIX(RANDOM_CONCAT(X,_s32))(randomp);
}

static inline s64 RANDOM_PREFIX(RANDOM_CONCAT(X,_i64))(RANDOM_CONCAT(X,_t) * randomp) {
  return RANDOM_PREFIX(RANDOM_CONCAT(X,_s64))(randomp);
}

static inline s128 RANDOM_PREFIX(RANDOM_CONCAT(X,_i128))(RANDOM_CONCAT(X,_t) * randomp) {
  return RANDOM_PREFIX(RANDOM_CONCAT(X,_s128))(randomp);
}

static inline f32 RANDOM_PREFIX(RANDOM_CONCAT(X,_f32))(RANDOM_CONCAT(X,_t) * randomp) {
  return (RANDOM_PREFIX(RANDOM_CONCAT(X,_u32))(randomp) >> 8) * 0x1.0p-24f;
}                               
                                
static inline f64 RANDOM_PREFIX(RANDOM_CONCAT(X,_f64))(RANDOM_CONCAT(X,_t) * randomp) {
  return (RANDOM_PREFIX(RANDOM_CONCAT(X,_u64))(randomp) >> 11) * 0x1.0p-53;
}

/* range */

static inline u32 RANDOM_PREFIX(RANDOM_CONCAT(X,_range_u32))(RANDOM_CONCAT(X,_t) * randomp, u32 low, u32 high) {
  u32 range = high - low + 1u;
  if (!range) return RANDOM_PREFIX(RANDOM_CONCAT(X,_u32))(randomp);
  u32 sample = RANDOM_PREFIX(RANDOM_CONCAT(X,_u32))(randomp);
  u64 product = (u64) sample * range;
  u32 low_word = (u32) product;
  if (low_word < range) {
    u32 threshold = (-range) % range;
    while (low_word < threshold) {
      sample   = RANDOM_PREFIX(RANDOM_CONCAT(X,_u32))(randomp);
      product  = (u64) sample * range;
      low_word = (u32) product;
    }
  }
  return low + (u32) (product >> 32);
}

static inline u64 RANDOM_PREFIX(RANDOM_CONCAT(X,_range_u64))(RANDOM_CONCAT(X,_t) * randomp, u64 low, u64 high) {
  u64 range = high - low + 1u;
  if (!range) return RANDOM_PREFIX(RANDOM_CONCAT(X,_u64))(randomp);
  u64 sample = RANDOM_PREFIX(RANDOM_CONCAT(X,_u64))(randomp);
  u128 product = (u128) sample * range;
  u64 low_word = (u64) product;
  if (low_word < range) {
    u64 threshold = (-range) % range;
    while (low_word < threshold) {
      sample   = RANDOM_PREFIX(RANDOM_CONCAT(X,_u64))(randomp);
      product  = (u128) sample * range;
      low_word = (u64) product;
    }
  }
  return low + (u64) (product >> 64);
}

static inline i32 RANDOM_PREFIX(RANDOM_CONCAT(X,_range_i32))(RANDOM_CONCAT(X,_t) * randomp, i32 low, i32 high) {
  u32 range = (u32) (high - low) + 1u;
  if (!range) return (i32) RANDOM_PREFIX(RANDOM_CONCAT(X,_u32))(randomp);
  u32 sample = RANDOM_PREFIX(RANDOM_CONCAT(X,_u32))(randomp);
  u64 product = (u64) sample * range;
  u32 low_word = (u32) product;
  if (low_word < range) {
    u32 threshold = (-range) % range;
    while (low_word < threshold) {
      sample   = RANDOM_PREFIX(RANDOM_CONCAT(X,_u32))(randomp);
      product  = (u64) sample * range;
      low_word = (u32) product;
    }
  }
  return low + (i32) (product >> 32);
}

static inline i64 RANDOM_PREFIX(RANDOM_CONCAT(X,_range_i64))(RANDOM_CONCAT(X,_t) * randomp, i64 low, i64 high) {
  u64 range = (u64) (high - low) + 1u;
  if (!range) return (i64) RANDOM_PREFIX(RANDOM_CONCAT(X,_u64))(randomp);
  u64 sample = RANDOM_PREFIX(RANDOM_CONCAT(X,_u64))(randomp);
  u128 product = (u128) sample * range;
  u64 low_word = (u64) product;
  if (low_word < range) {
    u64 threshold = (-range) % range;
    while (low_word < threshold) {
      sample   = RANDOM_PREFIX(RANDOM_CONCAT(X,_u64))(randomp);
      product  = (u128) sample * range;
      low_word = (u64) product;
    }
  }
  return low + (i64) (product >> 64);
}

static inline f32 RANDOM_PREFIX(RANDOM_CONCAT(X,_range_f32))(RANDOM_CONCAT(X,_t) * randomp, f32 low, f32 high) {
  return low + RANDOM_PREFIX(RANDOM_CONCAT(X,_f32))(randomp) * (high - low);
}

static inline f64 RANDOM_PREFIX(RANDOM_CONCAT(X,_range_f64))(RANDOM_CONCAT(X,_t) * randomp, f64 low, f64 high) {
  return low + RANDOM_PREFIX(RANDOM_CONCAT(X,_f64))(randomp) * (high - low);
}

#undef X
#undef X_PROVES_RULES
#undef X_NEXT_WIDTH
