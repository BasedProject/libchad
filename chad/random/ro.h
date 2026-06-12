#ifndef RANDOM_RO_H_
#define RANDOM_RO_H_

#include <stdint.h>

/* note that this will absolutely explode with libchad hence the prefixing */

static inline
uint32_t random_rol32(uint32_t x, unsigned int n)
{ return (n &= 31) ? (x << n) | (x >> (32 - n)) : x; }

static inline
uint64_t random_rol64(uint64_t x, unsigned int n)
{ return (n &= 63) ? (x << n) | (x >> (64 - n)) : x; }

static inline
uint32_t random_ror32(uint32_t x, unsigned int n)
{ return (n &= 31) ? (x >> n) | (x << (32 - n)) : x; }

#endif /* RANDOM_RO_H_ */
