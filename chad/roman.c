#include "roman.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* XXX todo:
 * * UTF variants (number forms block + combining overline)
 * * 'N' is often used to denote the value zero as an extension
 * * there is an extension to the roman system that adds fractions
 */

char * long2roman(long l, char * buffer) {
  #define form_string(decriment, appendage_a, optional_appendage_b) do {\
    *buffer = appendage_a;                                              \
    ++buffer;                                                           \
    if (optional_appendage_b) {                                         \
        *buffer = optional_appendage_b;                                 \
        ++buffer;                                                       \
    }                                                                   \
    l -= decriment;                                                     \
  } while (0)

    char * r = buffer;

    if (l < 1
    ||  l > ROMAN_MAX) {
	    *buffer = '\0';
        errno = ERANGE;
	    return r;
    }

    memset(buffer, 0, ROMAN_RENDERED_MAX);

    if (l >= ROMAN_Z)           { form_string(ROMAN_Z,           'Z', '\0'); }
    if (l >= ROMAN_Z - ROMAN_Y) { form_string(ROMAN_Z - ROMAN_Y, 'Y',  'Z'); }
    while (l >= ROMAN_Y)        { form_string(ROMAN_Y,           'Y', '\0'); }
    if (l >= ROMAN_Y - ROMAN_W) { form_string(ROMAN_Y - ROMAN_W, 'W',  'Y'); }
    if (l >= ROMAN_N)           { form_string(ROMAN_N,           'N', '\0'); }
    if (l >= ROMAN_N - ROMAN_W) { form_string(ROMAN_N - ROMAN_W, 'W',  'N'); }
    while (l >= ROMAN_W)        { form_string(ROMAN_W,           'W', '\0'); }
    if (l >= ROMAN_W - ROMAN_U) { form_string(ROMAN_W - ROMAN_U, 'U',  'W'); }
    if (l >= ROMAN_B)           { form_string(ROMAN_B,           'B', '\0'); }
    if (l >= ROMAN_B - ROMAN_U) { form_string(ROMAN_B - ROMAN_U, 'U',  'B'); }
    while (l >= ROMAN_U)        { form_string(ROMAN_U,           'U', '\0'); }
    if (l >= ROMAN_U - ROMAN_S) { form_string(ROMAN_U - ROMAN_S, 'S',  'U'); }
    if (l >= ROMAN_T)           { form_string(ROMAN_T,           'T', '\0'); }
    if (l >= ROMAN_T - ROMAN_S) { form_string(ROMAN_T - ROMAN_S, 'S',  'T'); }
    while (l >= ROMAN_S)        { form_string(ROMAN_S,           'S', '\0'); }
    if (l >= ROMAN_S - ROMAN_Q) { form_string(ROMAN_S - ROMAN_Q, 'Q',  'S'); }
    if (l >= ROMAN_R)           { form_string(ROMAN_R,           'R', '\0'); }
    if (l >= ROMAN_R - ROMAN_Q) { form_string(ROMAN_R - ROMAN_Q, 'Q',  'R'); }
    while (l >= ROMAN_Q)        { form_string(ROMAN_Q,           'Q', '\0'); }
    if (l >= ROMAN_Q - ROMAN_M) { form_string(ROMAN_Q - ROMAN_M, 'M',  'Q'); }
    if (l >= ROMAN_P)           { form_string(ROMAN_P,           'P', '\0'); }
    if (l >= ROMAN_P - ROMAN_M) { form_string(ROMAN_P - ROMAN_M, 'M',  'P'); }
    while (l >= ROMAN_M)        { form_string(ROMAN_M,           'M', '\0'); }
    if (l >= ROMAN_M - ROMAN_C) { form_string(ROMAN_M - ROMAN_C, 'C',  'M'); }
    if (l >= ROMAN_D)           { form_string(ROMAN_D,           'D', '\0'); }
    if (l >= ROMAN_D - ROMAN_C) { form_string(ROMAN_D - ROMAN_C, 'C',  'D'); }
    while (l >= ROMAN_C)        { form_string(ROMAN_C,           'C', '\0'); }
    if (l >= ROMAN_C - ROMAN_X) { form_string(ROMAN_C - ROMAN_X, 'X',  'C'); }
    if (l >= ROMAN_L)           { form_string(ROMAN_L,           'L', '\0'); }
    if (l >= ROMAN_L - ROMAN_X) { form_string(ROMAN_L - ROMAN_X, 'X',  'L'); }
    while (l >= ROMAN_X)        { form_string(ROMAN_X,           'X', '\0'); }

    switch (l) {
        case 9:
            *buffer++ = 'I';
            *buffer++ = 'X';
            break;

        case 8:
            *buffer++ = 'V';
            *buffer++ = 'I';
            *buffer++ = 'I';
            *buffer++ = 'I';
            break;

        case 7:
            *buffer++ = 'V';
            *buffer++ = 'I';
            *buffer++ = 'I';
            break;

        case 6:
            *buffer++ = 'V';
            *buffer++ = 'I';
            break;

        case 4:
            *buffer++ = 'I';
        case 5:
            *buffer++ = 'V';
            break;

        case 3:
            *buffer++ = 'I';
        case 2:
            *buffer++ = 'I';
        case 1:
            *buffer++ = 'I';
            break;
    }

    return r;
  #undef form_string
}

size_t long2roman_len(long l) {
    char buffer[ROMAN_RENDERED_MAX];
    long2roman(l, buffer);
    return strlen(buffer);
}

long roman2long(const char * roman) {
    long r = 0;

    for (; *roman; roman++) {
	    /* Check for four of a letter in a fow
         */
	    if ((*(roman + 1) && *(roman + 2) && *(roman + 3))
	    &&  (*roman == *(roman + 1))
	    &&  (*roman == *(roman + 2))
        &&  (*roman == *(roman + 3))) {
	        return -1;
        }

	    /* Check for two five type numbers
         */
	    if (((*roman == 'V') && (*(roman + 1) == 'V'))
	    ||  ((*roman == 'L') && (*(roman + 1) == 'L'))
	    ||  ((*roman == 'D') && (*(roman + 1) == 'D'))
	    ||  ((*roman == 'P') && (*(roman + 1) == 'P'))
	    ||  ((*roman == 'R') && (*(roman + 1) == 'R'))
	    ||  ((*roman == 'T') && (*(roman + 1) == 'T'))
	    ||  ((*roman == 'B') && (*(roman + 1) == 'B'))
	    ||  ((*roman == 'N') && (*(roman + 1) == 'N'))
	    ||  ((*roman == 'Z') && (*(roman + 1) == 'Z'))) {
	        return -1;
        }

	    /* Check for two lower characters before a larger one
         */
	    if ((roman_char2long(*roman) == roman_char2long(*(roman + 1))) && (*(roman + 2))
	    &&  (roman_char2long(*(roman + 1)) < roman_char2long(*(roman + 2)))) {
	        return -1;
        }

	    /* Check for the same character on either side of a larger one
         */
	    if ((*(roman + 1) && *(roman + 2))
	    && (roman_char2long(*roman) == roman_char2long(*(roman + 2)))
	    && (roman_char2long(*roman) <  roman_char2long(*(roman + 1)))) {
	        return -1;
        }

	    /* Check for illegal nine type numbers */
	    if (!strncmp (roman, "LXL", 3)
        ||  !strncmp (roman, "DCD", 3)
	    ||  !strncmp (roman, "PMP", 3)
        ||  !strncmp (roman, "RQR", 3)
	    ||  !strncmp (roman, "TST", 3)
        ||  !strncmp (roman, "BUB", 3)
	    ||  !strncmp (roman, "NWN", 3)
        ||  !strncmp (roman, "VIV", 3)) {
	        return -1;
        }

	    if (roman_char2long(*roman) < roman_char2long(*(roman + 1))) {
	        /* check that subtracted roman_char2longis at least 10% larger, 
	         * i.e. 1990 is not MXM, but MCMXC
             */
	        if ((10 * roman_char2long(*roman)) < roman_char2long(*(roman + 1))) {
	            return -1;
            }

	        /* check for double subtraction, i.e. IVX
             */
	        if (roman_char2long(*(roman + 1)) <= roman_char2long(*(roman + 2))) {
	            return -1;
            }

	        /* check for subtracting by a number starting with a 5
	         * ie.: VX, LD LM
             */
	        if (*roman == 'V'
            ||  *roman == 'L'
            ||  *roman == 'D'
	        ||  *roman == 'P'
            ||  *roman == 'R'
            ||  *roman == 'T'
	        ||  *roman == 'B'
            ||  *roman == 'N') {
	            return -1;
            }

	        r += roman_char2long(*(roman + 1)) - roman_char2long(*roman);

	        ++roman;
	    } else {
	        r += roman_char2long(*roman);
	    }
    }

    return r;
}


long roman_char2long(char c) {
    switch (c) {
        case 'I': return ROMAN_I;
        case 'V': return ROMAN_V;
        case 'X': return ROMAN_X;
        case 'L': return ROMAN_L;
        case 'C': return ROMAN_C;
        case 'D': return ROMAN_D;
        case 'M': return ROMAN_M;
        case 'P': return ROMAN_P;
        case 'Q': return ROMAN_Q;
        case 'R': return ROMAN_R;
        case 'S': return ROMAN_S;
        case 'T': return ROMAN_T;
        case 'U': return ROMAN_U;
        case 'B': return ROMAN_B;
        case 'W': return ROMAN_W;
        case 'N': return ROMAN_N;
        case 'Y': return ROMAN_Y;
        case 'Z': return ROMAN_Z;
        default:  return 0;
    }
}
