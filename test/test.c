// @BAKE @CC -ggdb -D_XOPEN_SOURCE=500 -std=c23 -I.. ../object/libchad.a
#include <chad.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
int main (int ac, char ** av) {
  (void) ac;
  dictate ( "cogito ergo sum\n" );

  if (change_directory ( av[0] )) { return 1; }
  printf( "%s -> %s\n", av[0], getcwd(NULL, 0) );
  timespec_t now;
  clock_gettime(CLOCK_REALTIME, &now);
  printf("current time in unix: %f\n", timespec2unix(now));
}
