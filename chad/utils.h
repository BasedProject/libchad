#ifndef CHAD_BITS_H
#define CHAD_BITS_H

#include <stdbool.h>
#include <iso646.h>

#define UNUSED(x) ((void)x)

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define CLAMP(a, b, c) ((a) < (b) ? (b) : (a) > (c) ? (c) : (a))


/* Convert argument to a string literal.
 */
#define _STRINGIFY(...) # __VA_ARGS__
#define STRINGIFY(...) _STRINGIFY(__VA_ARGS__)

/* Prevent argument from being expended as a macro.
 * Named after the POSIX shell rule that quoted strings are not checked for aliases.
 */
#define EMPTY()
#define QUOTE(id) id EMPTY()

// could be a generic
static inline
long map(
    long x,
    long in_min,
    long in_max,
    long out_min,
    long out_max
) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif
