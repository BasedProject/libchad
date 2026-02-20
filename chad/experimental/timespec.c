#include <chad/experimental/timespec.h>

/* --- conversion --- */

double timespec2unix(timespec_t ts)
{ return (double) ts.tv_sec + ((double) ts.tv_nsec / TIMESPEC_HZ); }

/* --- math --- */

timespec_t timespec_add(timespec_t a, timespec_t b) {
  a.tv_sec += b.tv_sec;
  a.tv_nsec += b.tv_nsec;
  if (a.tv_nsec >= TIMESPEC_HZ) {
    a.tv_sec++;
    a.tv_nsec -= TIMESPEC_HZ;
  }
  return a;
}

timespec_t timespec_sub(timespec_t a, timespec_t b) {
  a.tv_sec -= b.tv_sec;
  a.tv_nsec -= b.tv_nsec;
  if (a.tv_nsec < 0) {
    a.tv_sec--;
    a.tv_nsec += TIMESPEC_HZ;
  }
  return a;
}

int timespec_cmp(timespec_t a, timespec_t b) {
  return a.tv_sec > b.tv_sec ?
    (1) :
    a.tv_sec < b.tv_sec ?
    (-1) :
    (
      a.tv_nsec > b.tv_nsec ?
      (1) :
      a.tv_nsec < b.tv_nsec ?
      (-1) : 0
      );
}

timespec_t timespec_max(timespec_t a, timespec_t b) {
  return a.tv_sec > b.tv_sec ?
    a :
    a.tv_sec < b.tv_sec ?
    b :
    (
      a.tv_nsec > b.tv_nsec ?
      a : b
      );
}

timespec_t timespec_min(timespec_t a, timespec_t b) {
  return a.tv_sec < b.tv_sec ?
    a :
    a.tv_sec > b.tv_sec ?
    b :
    (
      a.tv_nsec < b.tv_nsec ?
      a : b
      );
}
