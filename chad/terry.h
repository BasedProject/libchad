#ifndef TERRY_H
#define TERRY_H

#if !(__STDC_VERSION__ >= 202311L)
#error >=C23 Required
#endif

// ---------------
// Primitive Types
// ---------------

#if 0
Please read the README provided here for type guarantees:
https://github.com/BasedProject/terry-h/blob/master/README.md

This header does not attempt to touch compiler builtins besides
__float80 as that is without a standardized type.
#endif

#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <float.h>

typedef int8_t  i8;
typedef int16_t i16;
typedef signed int i16x;
typedef int32_t i32;
typedef int64_t i64;

typedef int8_t  s8;
typedef int16_t s16;
typedef signed int s16x;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef unsigned int u16x;
typedef uint32_t u32;
typedef uint64_t u64;

typedef signed   _BitInt(128) i128;
typedef signed   _BitInt(128) s128;
typedef unsigned _BitInt(128) u128;

typedef i8 I8;
typedef i16 I16;
typedef i16x I16x;
typedef i32 I32;
typedef i64 I64;

typedef s8 S8;
typedef s16 S16;
typedef s16x S16x;
typedef s32 S32;
typedef s64 S64;

typedef u8 U8;
typedef u16 U16;
typedef u16x U16x;
typedef u32 U32;
typedef u64 U64;

typedef i128 I128;
typedef s128 S128;
typedef u128 U128;

#if __STDC_IEC_60559_TYPES__ >= 202311L
# define FLOAT_128 202605L
# define FLOAT_COMMON 202605L
  typedef _Float32 f32;
  typedef _Float64 f64;
  typedef _Float128 f128;
#else
# define FLOAT_COMMON 202605L
  static_assert(sizeof(float) * CHAR_BIT == 32, "float != f32");
  static_assert(sizeof(double) * CHAR_BIT == 64, "double != f64");
  typedef float f32;
  typedef double f64;
// note that this marco check would be a size check like above if it was possible
# if LDBL_MANT_DIG == 113
#   define FLOAT_128 202605L
    typedef long double f128;
# endif
#endif

#if __has_extension(__float80)
# define FLOAT_80 202605L
  typedef __float80 f80;
#elif LDBL_MANT_DIG == 64
# define FLOAT_80 202605L
  typedef long double f80;
#endif

#ifdef FLOAT_COMMON
typedef f32 F32;
typedef f64 F64;
#endif

#ifdef FLOAT_80
typedef f80 F80;
#endif

#ifdef FLOAT_128
typedef f128 F128;
#endif

// It is expectant of the standard of __STDC_IEC_60559_DFP__ for 32/64/128 to be a package
#if __STDC_IEC_60559_DFP__ >= 202311L || __has_extension(__Decimal32)
#define DECIMAL_COMMON 202605L
typedef _Decimal32  d32;
typedef _Decimal64  d64;
typedef _Decimal128 d128;
#endif


#ifdef DECIMAL_COMMON
typedef d32  D32;
typedef d64  D64;
typedef d128 D128;
#endif

typedef unsigned char uchar;
typedef signed char schar;      /* footgun */

typedef uchar UCHAR;
typedef schar SCHAR;

// ------------------
// Bitwise operations
// ------------------

#include <stdbit.h>

#define rotate_right stdc_rotate_right
#define rotate_left stdc_rotate_left
#define bit_floor stdc_bit_floor
#define bit_ceil stdc_bit_ceil
#define bit_width stdc_bit_width
#define bit_count_ones stdc_bit_count_ones
#define bit_count_zeros stdc_bit_count_zeros
#define first_trailing_one stdc_first_trailing_one
#define first_trailing_zero stdc_first_trailing_zero
#define first_leading_one stdc_first_leading_one
#define first_leading_zero stdc_first_leading_zero
#define trailing_ones stdc_trailing_ones
#define trailing_zeros stdc_trailing_zeros
#define leading_ones stdc_leading_ones
#define leading_zeros stdc_leading_zeros

#endif
