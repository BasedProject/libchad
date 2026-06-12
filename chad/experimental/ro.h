#ifndef CHAD_RO_H_
#define CHAD_RO_H_

/* rol */

#define rol(x, n) _Generic((x),                     \
    uint8_t :  rol8,  uint16_t : rol16,            \
    uint32_t : rol32, uint64_t : rol64,            \
    default: rol32)((x), (n))

static inline
uint8_t  rol8 (uint8_t x,  unsigned int n)
{ return (n &=  7) ? (x << n) | (x >> (8  - n)) : x; }

static inline
uint16_t rol16(uint16_t x, unsigned int n)
{ return (n &= 15) ? (x << n) | (x >> (16 - n)) : x; }

static inline
uint32_t rol32(uint32_t x, unsigned int n)
{ return (n &= 31) ? (x << n) | (x >> (32 - n)) : x; }

static inline
uint64_t rol64(uint64_t x, unsigned int n)
{ return (n &= 63) ? (x << n) | (x >> (64 - n)) : x; }

/* ror */

#define ror(x, n) _Generic((x),                     \
    uint8_t :  ror8,  uint16_t : ror16,            \
    uint32_t : ror32, uint64_t : ror64,            \
    default: rol32)((x), (n))

static inline
uint8_t  ror8 (uint8_t x,  unsigned int n)
{ return (n &=  7) ? (x >> n) | (x << (8  - n)) : x; }

static inline
uint16_t ror16(uint16_t x, unsigned int n)
{ return (n &= 15) ? (x >> n) | (x << (16 - n)) : x; }

static inline
uint32_t ror32(uint32_t x, unsigned int n)
{ return (n &= 31) ? (x >> n) | (x << (32 - n)) : x; }

static inline
uint64_t ror64(uint64_t x, unsigned int n)
{ return (n &= 63) ? (x >> n) | (x << (64 - n)) : x; }

#endif
