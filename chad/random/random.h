#ifndef RANDOM_H_
#define RANDOM_H_

#if 0
RATIFIED GENERIC INTERFACE:

rng_t rng_init(NULLABLE const char * buffer, size_t length);
<type> rng_<type>(rng_t * rng);

NONGENERIC, ALWAYS PROVIDED:
<native> rng_init_raw(...);     /* usually u<size> */
<native> rng_next(rng_t * rng);
#endif

#include <string.h>
#include <terry.h>
#include "bits.h"
#include "lcg.h"
#include "lcg2.h"
#include "mt19937.h"
#include "pcg.h"
#include "photon.h"
#include "romuduo.h"
#include "splitmix.h"
#include "wy.h"
#include "xoroshiro.h"
#include "xorshift.h"

/* global interface */
#include "grand.h"

#define random_i32(T) random_s32(T)
#define random_i64(T) random_s64(T)
#define random_i128(T) random_s128(T)

#define random_s32(T)   _Generic((T)                       , lcg_t       : lcg_s32        , lcg2_t     : lcg2_s32      , mt19937_t  : mt19937_s32  , \
                                      pcg_t    : pcg_s32   , photon_t    : photon_s32     , romuduo_t  : romuduo_s32   , splitmix_t : splitmix_s32 , \
                                      wy_t     : wy_s32    , xoroshiro_t : xoroshiro_s32  , xorshift_t : xorshift_s32 )((T))

#define random_s64(T)   _Generic((T)                       , lcg_t       : lcg_s64        , lcg2_t     : lcg2_s64      , mt19937_t  : mt19937_s64  , \
                                      pcg_t    : pcg_s64   , photon_t    : photon_s64     , romuduo_t  : romuduo_s64   , splitmix_t : splitmix_s64 , \
                                      wy_t     : wy_s64    , xoroshiro_t : xoroshiro_s64  , xorshift_t : xorshift_s64 )((T))

#define random_s128(T)  _Generic((T)                       , lcg_t       : lcg_s128       , lcg2_t     : lcg2_s128     , mt19937_t  : mt19937_s128  , \
                                      pcg_t    : pcg_s128  , photon_t    : photon_s128    , romuduo_t  : romuduo_s128  , splitmix_t : splitmix_s128 , \
                                      wy_t     : wy_s128   , xoroshiro_t : xoroshiro_s128 , xorshift_t : xorshift_s128)((T))

#define random_u32(T)   _Generic((T)                       , lcg_t       : lcg_u32        , lcg2_t     : lcg2_u32      , mt19937_t  : mt19937_u32  , \
                                      pcg_t    : pcg_u32   , photon_t    : photon_u32     , romuduo_t  : romuduo_u32   , splitmix_t : splitmix_u32 , \
                                      wy_t     : wy_u32    , xoroshiro_t : xoroshiro_u32  , xorshift_t : xorshift_u32 )((T))

#define random_u64(T)   _Generic((T)                       , lcg_t       : lcg_u64        , lcg2_t     : lcg2_u64      , mt19937_t  : mt19937_u64  , \
                                      pcg_t    : pcg_u64   , photon_t    : photon_u64     , romuduo_t  : romuduo_u64   , splitmix_t : splitmix_u64 , \
                                      wy_t     : wy_u64    , xoroshiro_t : xoroshiro_u64  , xorshift_t : xorshift_u64 )((T))

#define random_u128(T)  _Generic((T)                       , lcg_t       : lcg_u128       , lcg2_t     : lcg2_u128     , mt19937_t  : mt19937_u128  , \
                                      pcg_t    : pcg_u128  , photon_t    : photon_u128    , romuduo_t  : romuduo_u128  , splitmix_t : splitmix_u128 , \
                                      wy_t     : wy_u128   , xoroshiro_t : xoroshiro_u128 , xorshift_t : xorshift_u128)((T))

#define random_f32(T)  _Generic((T)                       , lcg_t       : lcg_f32       , lcg2_t     : lcg2_f32     , mt19937_t  : mt19937_f32  , \
                                      pcg_t    : pcg_f32  , photon_t    : photon_f32    , romuduo_t  : romuduo_f32  , splitmix_t : splitmix_f32 , \
                                      wy_t     : wy_f32   , xoroshiro_t : xoroshiro_f32 , xorshift_t : xorshift_f32)((T))

#define random_f64(T)  _Generic((T)                       , lcg_t       : lcg_f64       , lcg2_t     : lcg2_f64     , mt19937_t  : mt19937_f64  , \
                                      pcg_t    : pcg_f64  , photon_t    : photon_f64    , romuduo_t  : romuduo_f64  , splitmix_t : splitmix_f64 , \
                                      wy_t     : wy_f64   , xoroshiro_t : xoroshiro_f64 , xorshift_t : xorshift_f64)((T))

#if 0
#ifdef FLOAT_80
#define random_f80(T)  _Generic((T)                       , lcg_t       : lcg_f80       , lcg2_t     : lcg2_f80     , mt19937_t  : mt19937_f80  , \
                                      pcg_t    : pcg_f80  , photon_t    : photon_f80    , romuduo_t  : romuduo_f80  , splitmix_t : splitmix_f80 , \
                                      wy_t     : wy_f80   , xoroshiro_t : xoroshiro_f80 , xorshift_t : xorshift_f80)((T))
#endif

#ifdef FLOAT_128
#define random_f128(T)  _Generic((T)                       , lcg_t       : lcg_f128       , lcg2_t     : lcg2_f128     , mt19937_t  : mt19937_f128  , \
                                      pcg_t    : pcg_f128  , photon_t    : photon_f128    , romuduo_t  : romuduo_f128  , splitmix_t : splitmix_f128 , \
                                      wy_t     : wy_f128   , xoroshiro_t : xoroshiro_f128 , xorshift_t : xorshift_f128)((T))
#endif
#endif

#endif /* RANDOM_H_ */
