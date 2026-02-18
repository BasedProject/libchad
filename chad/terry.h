#ifndef TERRY_H
#define TERRY_H

#if 0
   Promises the most accurate primitives as are allowable by (recent) compiler version and C standard.
   Primitivie types:
   signed int : i8>i128, s8>s128
   unsigned int : u8>u128
   float  : f, f32
   double : fl, f64
   long double : fll, f128

   NO_128_TYPES will be defined when i128, s128, u128 are absent.
   NO_F_TYPE_NAME will remove hazardous declarations of f, fl, and fll.

   All floating bitmarked types will have F<NUM>_PRECISE defined
   if they are specified to that precise number of bits.

   Tested to work with gcc 14.2.0 and clang 19.1.7 on Debian // XXX: auto tests / auto comment
   Backwards compat for gcc 14.2.0
   Not robustly tested, please report issues.

   --- Definitions ---

   // XXX too *many* macros

   Defining the following will change behavior within the typesystem.
   the IMPRECISE groupings will always be provided with their respective types are present in full.

#define TERRY_FLOAT_IMPRECISE       /* supergroup of the below two groups */
#define TERRY_SMALL_FLOAT_IMPRECISE /* groups the two below together */
#define FLOAT_IS_F32
#define DOUBLE_IS_F64
#define TERRY_LARGE_FLOAT_IMPRECISE /* groups the two below together */
#define LONG_DOUBLE_IS_F80
#define LONG_DOUBLE_IS_F128
#define NO_128_TYPES                /* removes 128 declarations */
#define NO_F_TYPE_NAME 		    /* removes hazardous f, fl, fll */
#endif

/* --- */

#include <stdint.h>

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#ifndef NO_F_TYPE_NAME
typedef float  f;
typedef double fl;
typedef long double fll;
#endif

#ifndef NO_128_TYPES
# if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202000L && defined(__GNUC__) && !defined(__clang__)) \
  || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
#   define PRECISE_128
    typedef signed   _BitInt(128) i128;
    typedef signed   _BitInt(128) s128;
    typedef unsigned _BitInt(128) u128;
# else
#  if __SIZEOF_INT128__ 	/* compiler specific macro */
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wpedantic"
#    define PRECISE_128
     typedef signed   __int128 i128;
     typedef signed   __int128 s128;
     typedef unsigned __int128 u128;
#    pragma GCC diagnostic pop
#  else
#    define NO_128_TYPES
#  endif
# endif
#endif

#if !(defined(__STDC_IEC_60559_BFP__) && defined(__STDC_IEC_60559_TYPES__))
#define TERRY_FLOAT_IMPRECISE
#endif

#ifdef TERRY_FLOAT_IMPRECISE
# define TERRY_SMALL_FLOAT_IMPRECISE
# define TERRY_LARGE_FLOAT_IMPRECISE
#endif

#ifdef TERRY_SMALL_FLOAT_IMPRECISE
# define FLOAT_IS_F32
# define DOUBLE_IS_F64
#endif

#ifdef TERRY_LARGE_FLOAT_IMPRECISE
# define LONG_DOUBLE_IS_F80
# define LONG_DOUBLE_IS_F128
#endif

/* You can treat floats like _Float32, and doubles like _Float64, however *THEY ARE NOT THE SAME THING*. */
/* go ask WG14 for the "why." GCC/Clang may complain but will work as expected. */

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202000L && defined(__GNUC__) && !defined(__clang__)) \
||  (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
# if defined(FLOAT_IS_F32) || defined(TERRY_SMALL_FLOAT_IMPRECISE)
    typedef float f32;
# else
#   define F32_PRECISE
    typedef _Float32 f32;
# endif

# if defined(DOUBLE_IS_F64) || defined(TERRY_LARGE_FLOAT_IMPRECISE)
    typedef double f64;
# else
#   define F64_PRECISE
    typedef _Float64 f64;
# endif

# if defined(__GNUC__) && !defined(__clang__)
#   define F80_PRECISE
    typedef __float80 f80;
# else
    #define LONG_DOUBLE_IS_F80
    typedef long double f80;
# endif

# if defined(LONG_DOUBLE_IS_F128) || defined(TERRY_LARGE_FLOAT_IMPRECISE)
    typedef long double f128;
# else
#   define F128_PRECISE
    typedef _Float128 f128;
# endif
#else
/* the below f32/64 definitions may behave erratically, as float != f32 && double != f64.
 * We're just doing this for the sake of defining something that will *probably* work in most cases.
 * Use newer C versions. */
# if defined(__GNUC__) && !defined(__clang__)
#   define TERRY_SMALL_FLOAT_IMPRECISE

#   define FLOAT_IS_F32
    typedef float  f32;
#   define DOUBLE_IS_F64
    typedef double f64;

#   if defined(LONG_DOUBLE_IS_F80)
      typedef long double  f80;
#   else
#     define F80_PRECISE
      typedef __float80 f80;
#   endif

#   if defined(LONG_DOUBLE_IS_F128)
      typedef long double  f128;
#   else
#     define F128_PRECISE
      typedef __float128 f128;
#   endif
# else
#   define TERRY_FLOAT_IMPRECISE
#   define TERRY_SMALL_FLOAT_IMPRECISE
#   define TERRY_LARGE_FLOAT_IMPRECISE
#   define FLOAT_IS_F32
    typedef float  f32;
#   define DOUBLE_IS_F64
    typedef double f64;
    /* Usually 10-bytes with 128-bit alignment */
#   define LONG_DOUBLE_IS_F80
    typedef long double f80;
#   define LONG_DOUBLE_IS_F128
    typedef long double f128;
# endif
#endif
#endif
