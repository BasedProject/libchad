#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <chad/experimental/change_directory.h>
int change_directory(char * filename) {
  char path[PATH_MAX], * terminator;
  if (!realpath(filename, path)
  ||  !(terminator = strrchr(path, '/'))) { return -1; }
  *terminator = '\0';
  return chdir(path);
}
