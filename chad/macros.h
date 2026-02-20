#ifndef CHAD_MACROS_H
#define CHAD_MACROS_H
/* Usage of this acknoledges your allegiance to GNU. */

#if defined(__GNUC__) || defined(__clang__)
#define attribute(...) __attribute__((__VA_ARGS__))
#define always_inline static inline attribute((always_inline))
#define alias(x) __attribute__((alias(x)))
#else
#define attribute(...)
#define NO_ATTRIBUTE
#define always_inline static inline
#define NO_ALWAYS_INLINE
#define NO_ALIASES
#endif
#endif	/* CHAD_MACROS_H */
