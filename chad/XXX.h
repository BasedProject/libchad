#ifndef XXX_H
#define XXX_H

/*
 * # XXX.h
 * 
 * > Analogous function to Perl's '...', warn() and die().
 * 
 * Contents:
 * * XXX()     - die because unimplemented
 * * die(msg)  - die with message
 * * warn(msg) - emit warning message
 * 
 * Example output:
 * `Unimplemented at test.c line 7.`
 * 
 * All macros wrap a function of the same name, meaning you can set debugger breakpoints at them.
 * 
 * All macros use the overridable macro `xxx_printf(invoker_fn, ...)`.
 * 
 * `XXX` can be used with or without trailing parenthesis.
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef xxx_printf
#define xxx_printf(invoker_fn, ...) \
    fprintf(stderr, __VA_ARGS__)
#endif

#define XXX__STRINGIFY(...) # __VA_ARGS__
#define XXX_STRINGIFY(...) XXX__STRINGIFY(__VA_ARGS__)

[[noreturn]]
static inline
void XXX(const char * const filename, const char * const line_number) {
    xxx_printf(XXX, "Unimplemented at %s line %s.\n", filename, line_number);
    abort();
}

static inline void xxx_nop(void) { return; }

#define XXX (void)(XXX(__FILE__, XXX_STRINGIFY(__LINE__) ), xxx_nop)

static inline
void warn(const char * const filename, const char * const line_number, const char * const message) {
    xxx_printf(warn, "Warning at %s line %s: %s.\n", filename, line_number, message);
}

#define warn(msg) warn(__FILE__, XXX_STRINGIFY(__LINE__), (msg))

static inline
void die(const char * const filename, const char * const line_number, const char * const message) {
    xxx_printf(die, "Died at %s line %s: %s.\n", filename, line_number, message);
    abort();
}

#define die(msg) die(__FILE__, XXX_STRINGIFY(__LINE__), (msg))

#endif
