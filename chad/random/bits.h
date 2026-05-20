#ifndef BITS_H_
#define BITS_H_
#define RANDOM_CONCAT_(a,b) a##b
#define RANDOM_CONCAT(a,b) RANDOM_CONCAT_(a,b)
#if defined(USE_RANDOM_PREFIX)
# define RANDOM_PREFIX(x) RANDOM_CONCAT_(random_, x)
#else
# define RANDOM_PREFIX(x) x
#endif

#include <terry.h>

u128 RANDOM_PREFIX(init_block)(const char * buffer, size_t length);

#endif /* BITS_H_ */
