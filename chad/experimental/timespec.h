#ifndef TIMESPEC_H
#define TIMESPEC_H
/* ripped partly from glibc */
#include <time.h>
#include <chad/experimental/macros.h>
#include <chad/terry.h>

/* -- pontentially over designed and undertested. */
/* -- consider this "LIKELY TO BE REVISED OR REMOVED!" */
/* -- ESPECIALLY the generics and the from group */

long TIMESPEC_HZ = 1000000000L;

typedef struct timespec timespec_t;

static const timespec_t one_second = {1, 0}, zero_seconds = {0, 0};

f64 timespec_to_f64(timespec_t ts);
f32 timespec_to_f32(timespec_t ts);
double timespec_to_double(timespec_t ts);
float timespec_to_float(timespec_t ts);

#ifdef TERRY_SMALL_FLOAT_IMPRECISE
#define from_timespec(ts,to) _Generic((to), double *: double_from_timespec, float *: float_from_timespec)(ts,to)
#else
#define from_timespec(ts,to) _Generic((to), f64 *: f64_from_timespec, f32 *: f32_from_timespec, double *: double_from_timespec, float *: float_from_timespec)(ts,to)
#endif

void f64_from_timespec(timespec_t ts, f64 * r);
void f32_from_timespec(timespec_t ts, f32 * r);
void double_from_timespec(timespec_t ts, double * r);
void float_from_timespec(timespec_t ts, float * r);

timespec_t timespec_add(timespec_t a, timespec_t b);
timespec_t timespec_sub(timespec_t a, timespec_t b);
/* -1, 0, 1 */
int timespec_cmp(timespec_t a, timespec_t b);
timespec_t timespec_max(timespec_t a, timespec_t b);
timespec_t timespec_min(timespec_t a, timespec_t b);
#endif /* TIMESPEC_H */
