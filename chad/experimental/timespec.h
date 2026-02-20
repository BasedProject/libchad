#ifndef TIMESPEC_H
#define TIMESPEC_H
/* ripped partly from glibc */

#include <time.h>
#include <chad/terry.h>

/* -- pontentially over designed and undertested. */
/* -- consider this "LIKELY TO BE REVISED OR REMOVED!" */
/* -- ESPECIALLY the generics and the from group */

long TIMESPEC_HZ = 1000000000L;

typedef struct timespec timespec_t;

static const timespec_t one_second = {1, 0}, zero_seconds = {0, 0};

double timespec2unix(timespec_t ts);

timespec_t timespec_add(timespec_t a, timespec_t b);
timespec_t timespec_sub(timespec_t a, timespec_t b);
/* -1, 0, 1 */
int timespec_cmp(timespec_t a, timespec_t b);
timespec_t timespec_max(timespec_t a, timespec_t b);
timespec_t timespec_min(timespec_t a, timespec_t b);
#endif /* TIMESPEC_H */
