#include <limits.h>
/* #include <stdlib.h> */
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <chad/experimental/change_directory.h>
/*  */
#include <stdio.h>
/*  */
int change_directory(const char * filename) {
  struct stat statistics;
  char path[PATH_MAX];
  strncpy(path, filename, PATH_MAX-1);

  if (stat(path, &statistics)) { return -1; }

  if (!S_ISDIR(statistics.st_mode)) {
    char * terminator = strrchr(path, '/');
    if (!terminator) { return -1; }
    *terminator = '\0';
  }

  return chdir(path);
}
