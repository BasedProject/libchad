#ifndef QX_H
#define QX_H

#ifdef __cplusplus
extern "C" {
#endif

/* # qx
 *
 * ## NAME
 * qx - execute system commands receive back the output
 *
 * ## SYNOPSIS
 */
extern char * qx(const char * const cmd);
/* ## DESCRIPTION
 * `qx()` is a small wrapper function to replicate Perl's `qx` in C.
 * It is intended for developer convenience.
 * The command argument is a pointer to a null-terminated
 * string containing a shell command line.
 * This command is passed to `/bin/sh` using the `-c` flag; interpretation,
 * if  any,  is  performed by the shell.
 *
 * ## RETURN VALUE
 * Upon successful return, the captured `stdout` and `stderr` of `cmd` is returned
 * in a dynamic string. Calling `free()` is the programmer's responsibility.
 *
 * If an error is encountered `NULL` is returned.
 * The shell returning a non-zero exit value is not considered an error.
 */

#ifdef __cplusplus
}
#endif

#endif
