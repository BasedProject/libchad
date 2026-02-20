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

#endif /* CHAD_MACROS_H */
