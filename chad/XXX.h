#ifndef XXX_H
#define XXX_H

/* Todo:
 * * warn variant
 */

#include <stdio.h>
#include <stdlib.h>


#define XXX__STRINGIFY(...) # __VA_ARGS__
#define XXX_STRINGIFY(...) XXX__STRINGIFY(__VA_ARGS__)

[[noreturn]]
static inline
void XXX(const char * const filename, const char * const line_number) {
    fprintf(stderr, "Unimplemented at %s line %s.\n", filename, line_number);
    abort();
}

static inline void xxx_nop(void) { return; }

#define XXX (void)(XXX(__FILE__, XXX_STRINGIFY(__LINE__) ), xxx_nop)

#endif
