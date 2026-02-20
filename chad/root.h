#ifdef CHAD_ROOT_H
#define CHAD_ROOT_H
#include <limits.h>
#include "macros.h"
/* check errno -- chdir */
always_inline void Root(char * filename) {
  extern char * realpath(const char * restrict path, char * restrict resolved_path);
  extern int chdir(const char * path);
  attribute(noreturn) void abort(void);
  char path[PATH_MAX], * terminator;
  if (!realpath(filename, path)) { return; }
  if ((terminator = strrchr(path, '/'))) {
    *terminator = '\0';
    chdir(path);
  }
}
#endif /* CHAD_ROOT_H */
