#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <chad/experimental/root.h>
void Root(char * filename) {
  char path[PATH_MAX], * terminator;
  if (!realpath(filename, path)) { return; }
  if ((terminator = strrchr(path, '/'))) {
    *terminator = '\0';
    chdir(path);
  }
}
