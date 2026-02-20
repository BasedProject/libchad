#ifndef TIMESPEC_H
#define TIMESPEC_H
/* ripped partly from glibc */
#include <time.h>
#include "macros.h"
#include "terry.h"

/* -- pontentially over designed and undertested. */
/* -- consider this "LIKELY TO BE REVISED OR REMOVED!" */
/* -- ESPECIALLY the generics and the from group */

long TIMESPEC_HZ = 1000000000L;

typedef struct timespec timespec_t;

static const timespec_t one_second = {1, 0}, zero_seconds = {0, 0};

always_inline f64 timespec_to_f64(timespec_t ts)
{ return (f64) ts.tv_sec + ((f64) ts.tv_nsec / TIMESPEC_HZ); }

always_inline f32 timespec_to_f32(timespec_t ts)
{ return (f32) ts.tv_sec + ((f32) ts.tv_nsec / TIMESPEC_HZ); }

#if defined(TERRY_SMALL_FLOAT_IMPRECISE) && !defined(NO_ALIASES)
always_inline double timespec_to_double(timespec_t ts) alias("timespec_to_f64");
always_inline float timespec_to_float(timespec_t ts) alias("timespec_to_f32");
#else
always_inline double timespec_to_double(timespec_t ts)
{ return (double) ts.tv_sec + ((double) ts.tv_nsec / TIMESPEC_HZ); }
always_inline float timespec_to_float(timespec_t ts)
{ return (float) ts.tv_sec + ((float) ts.tv_nsec / TIMESPEC_HZ); }
#endif


#ifdef TERRY_SMALL_FLOAT_IMPRECISE
#define _from_timespec(ts,to) _Generic((to), double *: double_from_timespec, float *: float_from_timespec)(ts,to)
#else
#define _from_timespec(ts,to) _Generic((to), f64 *: f64_from_timespec, f32 *: f32_from_timespec, double *: double_from_timespec, float *: float_from_timespec)(ts,to)
#endif

always_inline void from_timespec(timespec_t ts, )

always_inline void f64_from_timespec(timespec_t ts, f64 * r)
{ *r = (f64) ts.tv_sec + ((f64) ts.tv_nsec / TIMESPEC_HZ); }

always_inline void f32_from_timespec(timespec_t ts, f32 * r)
{ *r = (f32) ts.tv_sec + ((f32) ts.tv_nsec / TIMESPEC_HZ); }

#if defined(TERRY_SMALL_FLOAT_IMPRECISE) && !defined(NO_ALIASES)
always_inline void double_from_timespec(timespec_t ts, double * r) alias("timespec_to_f64");
always_inline void float_from_timespec(timespec_t ts, float * r) alias("timespec_to_f32");
#else
always_inline void double_from_timespec(timespec_t ts, double * r)
{ *r = (double) ts.tv_sec + ((double) ts.tv_nsec / TIMESPEC_HZ); }
always_inline void float_from_timespec(timespec_t ts, float * r)
{ *r = (float) ts.tv_sec + ((float) ts.tv_nsec / TIMESPEC_HZ); }
#endif

always_inline timespec_t timespec_add(timespec_t a, timespec_t b) {
  a.tv_sec += b.tv_sec;
  a.tv_nsec += b.tv_nsec;
  if (a.tv_nsec >= TIMESPEC_HZ) {
    a.tv_sec++;
    a.tv_nsec -= TIMESPEC_HZ;
  }
  return a;
}

always_inline timespec_t timespec_sub(timespec_t a, timespec_t b) {
  a.tv_sec -= b.tv_sec;
  a.tv_nsec -= b.tv_nsec;
  if (a.tv_nsec < 0) {
    a.tv_sec--;
    a.tv_nsec += TIMESPEC_HZ;
  }
  return a;
}

always_inline int timespec_cmp(timespec_t a, timespec_t b) {
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

always_inline timespec_t timespec_max(timespec_t a, timespec_t b) {
  return a.tv_sec > b.tv_sec ?
    a :
    a.tv_sec < b.tv_sec ?
    b :
    (
      a.tv_nsec > b.tv_nsec ?
      a : b
      );
}

always_inline timespec_t timespec_min(timespec_t a, timespec_t b) {
  return a.tv_sec < b.tv_sec ?
    a :
    a.tv_sec > b.tv_sec ?
    b :
    (
      a.tv_nsec < b.tv_nsec ?
      a : b
      );
}

#endif	/* TIMESPEC_H */
