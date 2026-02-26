#ifndef CHAD_ROT_H_
#define CHAD_ROT_H_

/* rotl */

#define rotl(x, n) _Generic((x),                     \
    uint8_t :  rotl8,  uint16_t : rotl16,            \
    uint32_t : rotl32, uint64_t : rotl64,            \
    default: rotl32)((x), (n))

static inline
uint8_t  rotl8 (uint8_t x,  unsigned int n)
{ return (n &=  7) ? (x << n) | (x >> (8  - n)) : x; }

static inline
uint16_t rotl16(uint16_t x, unsigned int n)
{ return (n &= 15) ? (x << n) | (x >> (16 - n)) : x; }

static inline
uint32_t rotl32(uint32_t x, unsigned int n)
{ return (n &= 31) ? (x << n) | (x >> (32 - n)) : x; }

static inline
uint64_t rotl64(uint64_t x, unsigned int n)
{ return (n &= 63) ? (x << n) | (x >> (64 - n)) : x; }

/* rotr */

#define rotr(x, n) _Generic((x),                     \
    uint8_t :  rotr8,  uint16_t : rotr16,            \
    uint32_t : rotr32, uint64_t : rotr64,            \
    default: rotl32)((x), (n))

static inline
uint8_t  rotr8 (uint8_t x,  unsigned int n)
{ return (n &=  7) ? (x >> n) | (x << (8  - n)) : x; }

static inline
uint16_t rotr16(uint16_t x, unsigned int n)
{ return (n &= 15) ? (x >> n) | (x << (16 - n)) : x; }

static inline
uint32_t rotr32(uint32_t x, unsigned int n)
{ return (n &= 31) ? (x >> n) | (x << (32 - n)) : x; }

static inline
uint64_t rotr64(uint64_t x, unsigned int n)
{ return (n &= 63) ? (x >> n) | (x << (64 - n)) : x; }

#endif
