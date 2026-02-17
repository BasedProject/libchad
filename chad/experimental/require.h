#ifndef REQUIRE_H
#define REQUIRE_H

#include <chad/experimental/bits.h>

/* Require macros for easy uniform error handling.
 * They can be used to replace repeated error handling logic
 *  or some messier solutions.
 *
 * REQUIRE() and REQUIRE_EX() assert a statement,
 *  on failure they invoke REQUIRE_TERMINATOR,
 *  on success they return the resulting value.
 *
 * REQUIRE_EX() takes a custom error value as its first argument,
 *  REQUIRE() assumes standard C truthliness.
 *
 * Example:
 *     int extreme_example(int i) {
 *         switch (i) {
 *             case 1: return 4;
 *             case 2: return 5;
 *             default: return 0;
 *         }
 *     }
 *     
 *     signed main(void) {
 *         FILE * f = REQUIRE(fopen("a.txt", "r"));
 *     
 *         REQUIRE(3 < 5);
 *     
 *         int i = REQUIRE(extreme_example(1));
 *     
 *         return 0;
 *     }
 * Possible (stderr) output:
 *     Required operation 'fopen("a.txt", "r")' failed.
 */

thread_local long long require_v;

#ifndef REQUIRE_TERMINATOR
# define REQUIRE_TERMINATOR(...) default_require_terminator(__VA_ARGS__)
#endif

[[ noreturn ]]
static inline
void require_default_terminator(const char * const argv) {
    fprintf(stderr, "Required operation '%s' failed.\n", argv);
    exit(1);
}

#define REQUIRE_EX(errval, ...) (typeof(__VA_ARGS__))( \
    (typeof(__VA_ARGS__))(require_v = (long long)(__VA_ARGS__)) != (typeof(__VA_ARGS__))errval \
    ? require_v \
    : (REQUIRE_TERMINATOR(STRINGIFY(__VA_ARGS__)), 0ll) \
)

#define REQUIRE(...) REQUIRE_EX(0ll, __VA_ARGS__)

#endif
