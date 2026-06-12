#ifndef ROMAN_H
#define ROMAN_H

#include <stddef.h>

/* Convert between numbers and their roman string representations.
 */

/* The alphabet of letters we use for spelling roman numbers.
 * I-M is standard while the characters above have the historical significance
 *  of a 90s developer making them the fuck up for a word processor named AbiWord.
 */
enum {
    ROMAN_I =           1,
    ROMAN_V =           5,
    ROMAN_X =          10,
    ROMAN_L =          50,
    ROMAN_C =         100,
    ROMAN_D =         500,
    ROMAN_M =       1'000,
    ROMAN_P =       5'000,
    ROMAN_Q =      10'000,
    ROMAN_R =      50'000,
    ROMAN_S =     100'000,
    ROMAN_T =     500'000,
    ROMAN_U =   1'000'000,
    ROMAN_B =   5'000'000,
    ROMAN_W =  10'000'000,
    ROMAN_N =  50'000'000,
    ROMAN_Y = 100'000'000,
    ROMAN_Z = 500'000'000,
};

/* The largest number we can handle.
 */
#define ROMAN_MAX 999'999'999

/* The maximum possible buffer size you would need for a roman number below ROMAN_MAX.
 * This has the decimal value of 888'888'888 and 36 bytes long without a null termination.
 */
#define ROMAN_RENDERED_MAX sizeof("ZYYYNWWWBUUUTSSSRQQQPMMMDCCCLXXXVIII")

/* Convert from long to roman and return the modified buffer argument.
 * If `l` is invalid, `buffer` is set to "" and `errno` is set to ERANGE.
 */
extern char * long2roman(long l, char * buffer);
/* Get the number of characters `l` will contain rendered.
 * Note that this is a strlen and not a sizeof.
 */
extern size_t long2roman_len(long l);
/* Convert from roman to long.
 * If `roman` is invalid, -1 is returned.
 */
extern long roman2long(const char * roman);
/* Perform character based lookup of the `ROMAN_*` enum.
 */
extern long roman_char2long(char c);

#endif
