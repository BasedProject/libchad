#ifndef CHAD_MACROS_H
#define CHAD_MACROS_H
/* Usage of this acknoledges your allegiance to GNU. */

/* make it such that [[attributes]] is used in C23 & use GCC otherwise */
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202000L)
#  define attribute(...) [[__VA_ARGS__]]
#else
# if defined(__GNUC__) || defined(__clang__)
#  define attribute(...) __attribute__((__VA_ARGS__))
# else
#   define attribute(...)
#   define NO_ATTRIBUTE
# endif
#endif

#if !defined(NO_ATTRIBUTE)
# define always_inline static inline attribute(always_inline)
# define alias(x) attribute(alias(x))
#else
# define always_inline static inline
# define NOT_ALWAYS_INLINE
# define NO_ALIASES
#endif

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define CLAMP(a,b,c) (a)<(b)?(b):(a)>(c)?(c):(a)

#endif /* CHAD_MACROS_H */
