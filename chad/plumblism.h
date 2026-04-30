#ifndef PLUMBLISM_H
#define PLUMBLISM_H

#include <stdio.h>

/* Legend:
 *  PBM -> Portable Bit Map
 *  PGM -> Portable Grey Map
 *  PPM -> Portable Pix Map
 *
 *  PBMplus -> PBM, PGM and PPM
 *  PNM -> Portable Any Map; synonym for PBMplus,
 *          I have no clue who came up with it
 */

typedef enum {
    /* NOTE:
     *  the order is significant,
     *  because it corresponds to the mime
     */
    PNM_BIT_ASCII = 1,
    PNM_GRE_ASCII,
    PNM_PIX_ASCII,
    PNM_BIT_BINARY,
    PNM_GRE_BINARY,
    PNM_PIX_BINARY,
} pnm_type_t;

/* Return PNM type.
 *  It is assumed that `f` has just been opened.
 *  Otherwise please `rewind(3)`.
 */
pnm_type_t get_pnm_type(FILE * f);

/* Return storage requirement.
 * `f` will be rewinded automatically.
 * `w`, `h` and `intensity` are nullable.
 * In case of a `PNM_BIT_*`, intensity will always be 1 (assuming success).
 */
int read_pnm_header(FILE * f, pnm_type_t type, int * w, int * h, int * intensity);

/* Store data in `b`.
 * `b` is assumed to have been allocated by the programmer
 * as according to the return value of `read_pnm_header`.
 * It is assumed that `read_pnm_header` has just been called on `f`,
 *  otherwise the file position pointer is going to be misaligned.
 */
int read_pnm_data(FILE * f, pnm_type_t type, int * b);

/* Write from `b` to `f`.
 * In case of a `PNM_BIT_*`, intensity is ignored.
 */
int write_pnm_file(FILE * f, pnm_type_t type, const int * b, int w, int h, int intensity);

/* ## Return value
 * `read_pnm_header` returns the number of bytes required to store the contents of `f`.
 * 
 * `read_pnm_data` and `write_pnm_file` return the amount of bytes I/O'd.
 *
 * On error, *-1* is returned.
 */

/* ## Notes
 * `f` should always be opened in text mode.
 */

#endif
