#include <chad/experimental/timespec.h>

/* --- conversion --- */

f64 timespec_to_f64(timespec_t ts)
{ return (f64) ts.tv_sec + ((f64) ts.tv_nsec / TIMESPEC_HZ); }

f32 timespec_to_f32(timespec_t ts)
{ return (f32) ts.tv_sec + ((f32) ts.tv_nsec / TIMESPEC_HZ); }

double timespec_to_double(timespec_t ts)
{ return (double) ts.tv_sec + ((double) ts.tv_nsec / TIMESPEC_HZ); }

float timespec_to_float(timespec_t ts)
{ return (float) ts.tv_sec + ((float) ts.tv_nsec / TIMESPEC_HZ); }

/* --- from --- */

void f64_from_timespec(timespec_t ts, f64 * r)
{ *r = (f64) ts.tv_sec + ((f64) ts.tv_nsec / TIMESPEC_HZ); }

void f32_from_timespec(timespec_t ts, f32 * r)
{ *r = (f32) ts.tv_sec + ((f32) ts.tv_nsec / TIMESPEC_HZ); }

void double_from_timespec(timespec_t ts, double * r)
{ *r = (double) ts.tv_sec + ((double) ts.tv_nsec / TIMESPEC_HZ); }

void float_from_timespec(timespec_t ts, float * r)
{ *r = (float) ts.tv_sec + ((float) ts.tv_nsec / TIMESPEC_HZ); }

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
