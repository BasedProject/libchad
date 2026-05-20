#ifndef RANDOM_ROTATE_H_
#define RANDOM_ROTATE_H_

#include <terry.h>

/* note that this will absolutely explode with libchad hence the prefixing */
/* C23 SHOULD provide these but they don't exist in my compiler... */

static inline
u32 random_rol32(u32 x, unsigned int n)
{ return (n &= 31) ? (x << n) | (x >> (32 - n)) : x; }

static inline
u64 random_rol64(u64 x, unsigned int n)
{ return (n &= 63) ? (x << n) | (x >> (64 - n)) : x; }

static inline
u32 random_ror32(u32 x, unsigned int n)
{ return (n &= 31) ? (x >> n) | (x << (32 - n)) : x; }

static inline
u32 random_ror64(u32 x, unsigned int n)
{ return (n &= 63) ? (x >> n) | (x << (64 - n)) : x; }

#endif /* RANDOM_ROTATE_H_ */
