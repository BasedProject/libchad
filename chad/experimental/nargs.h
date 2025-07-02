#ifndef CHAD_NARGS_H
#define CHAD_NARGS_H

#include "nargs.h"
#include <stdarg.h>

#define _max_function(T) \
static inline _max_function_ ## T (size_t n, ...) { \
    va_list args; \
    va_start(args, n); \
    T r = 0; \
    for (size_t i = 0; i < n; i++) { \
        T c = 
        if ()
    } \

    return r;
}

#endif
