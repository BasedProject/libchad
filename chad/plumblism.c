#include "plumblism.h"

#include <stdio.h>
#include <stdbool.h>

/* Every problem is a parsing problem, if you hate yourself enough.
 *                                      - Anon; all rights reserved
 */
typedef enum {
    INITIAL,
    IN_NUMBER,
    IN_COMMENT,
} state_t;
#define DIGIT '0':                                    \
              case '1': case '2': case '3': case '4': \
              case '5': case '6': case '7': case '8': \
              case '9'
#define WS    ' ': case '\t': case '\n': case '\v': case '\f': case '\r'
#define BEGIN(s) state = s
#define DIGIT_BUFFER_TO_INT(b, n, r) \
  r = 0;                             \
  for (int i = 0; i < n; i++) {      \
      r = r * 10 + (b[i] - '0');     \
  }


// NOTE: 
//  There is an edgacase where a number is followed by a comment
//  > 10#comment\n10
//  Is this allowed?
//  Does this yield 10-10 or 1010?
//  We dont know!

pnm_type_t get_pnm_type(FILE * f) {
    char magic[2];

    magic[0] = fgetc(f);
    magic[1] = fgetc(f);
 
    if (magic[0] != 'P') { return -1; }

    return magic[1] - '0';
}

// --- Lexers
static
int lex_header(FILE * f) {
    int r;
    char digit_buffer[12];
    int digit_buffer_empty_top = 0;

    state_t state = INITIAL;

    int c;
    do {
        c = fgetc(f);
        switch (state) {
            case INITIAL: {
                switch (c) {
                    case DIGIT: {
                        BEGIN(IN_NUMBER);
                        digit_buffer[digit_buffer_empty_top++] = c;
                    } break;
                    case '#': BEGIN(IN_COMMENT); break;
                    case WS: { ; } break;
                    default: return -1;
                }
            } break;

            case IN_NUMBER: {
                switch (c) {
                    case DIGIT: {
                        digit_buffer[digit_buffer_empty_top++] = c;
                    } break;
                    case WS: {
                        DIGIT_BUFFER_TO_INT(digit_buffer, digit_buffer_empty_top, r);
                    } return r;
                    default: return -1;
                }
            } break;

            case IN_COMMENT: {
                if (c == '\n') { BEGIN(INITIAL); }
            } break;
        }
    } while (c != EOF);

    return -1;
}

static
int lex_data(FILE * f, int * b) {
    int r = 0;

    int c;
    state_t state = INITIAL;
    char digit_buffer[12];
    int digit_buffer_empty_top = 0;
    while ((c = fgetc(f)) != EOF) {
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wswitch"
        switch (state) {
            case INITIAL: {
                switch (c) {
                    case DIGIT: {
                        digit_buffer[digit_buffer_empty_top++] = c;
                    } break;

                    case WS: {
                        int i;
                        DIGIT_BUFFER_TO_INT(digit_buffer, digit_buffer_empty_top, i);
                        b[r++] = i;
                    } break;

                    case '#': { BEGIN(IN_COMMENT); } break;

                    default: return -1;
                }
            } break;
            case IN_COMMENT: {
                if (c == '\n') { BEGIN(INITIAL); }
            } break;
        }
      #pragma GCC diagnostic pop
    }

    return r;
}


// --- Readers
int read_pnm_header(FILE * f, pnm_type_t type, int * w, int * h, int * intensity) {
    int w_, h_, intensity_;

    rewind(f);
    fgetc(f);
    fgetc(f);

    w_ = lex_header(f); if (w_ == -1) { return -1; }
    h_ = lex_header(f); if (h_ == -1) { return -1; }
    if (type == PNM_BIT_ASCII
    ||  type == PNM_BIT_BINARY) {
        intensity_ = 1;
    } else {
        intensity_ = lex_header(f);
        if (intensity_ == -1) { return -1; }
    }

    if (w        ) { *w         = w_        ; }
    if (h        ) { *h         = h_        ; }
    if (intensity) { *intensity = intensity_; }

    return (*w) * (*h) * sizeof(int);
}

static
int read_pnm_bit_ascii_data(FILE * f, int * b) {
    int r = 0;

    int c;
    state_t state = INITIAL;
    while ((c = fgetc(f)) != EOF) {
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wswitch"
        switch (state) {
            case INITIAL: {
                switch (c) {
                    case '0': case '1': {
                        b[r++] = c - '0';
                    } break;
                    case WS: { ; } break;
                    case '#': { BEGIN(IN_COMMENT); } break;
                    default: return -1;
                }
            } break;

            case IN_COMMENT: {
                if (c == '\n') { BEGIN(INITIAL); }
            } break;
        }
      #pragma GCC diagnostic pop
    }

    return r;
}

static
int read_pnm_bit_binary_data(FILE * f, int * b) {
    int r = 0;
    
    int c;
    while ((c = fgetc(f)) != EOF) {
        for (int i = 0; i < 8; i++) {
            b[r++] = (c >> (7-i)) & 0x1;
        }
    }

    return r;
}

static
int read_pnm_gray_ascii_data(FILE * f, int * b) {
    return lex_data(f, b);
}

static inline
int read_pnm_gray_binary_data(FILE * f, int * b) {
    int r = 0;

    int c;
    while ((c = fgetc(f)) != EOF) { b[r++] = c; }

    return r;
}

static
int read_pnm_pix_ascii_data(FILE * f, int * b) {
    const int i = lex_data(f, b);
    return (i % 3 == 0 ? i : -1);
}

static
int read_pnm_pix_binary_data(FILE * f, int * b) {
    return read_pnm_gray_binary_data(f, b);
}

int read_pnm_data(FILE * f, pnm_type_t type, int * b) {
    switch (type) {
        case PNM_BIT_ASCII:  return read_pnm_bit_ascii_data(f, b);
        case PNM_GRE_ASCII:  return read_pnm_gray_ascii_data(f, b);
        case PNM_PIX_ASCII:  return read_pnm_pix_ascii_data(f, b);
        case PNM_BIT_BINARY: return read_pnm_bit_binary_data(f, b);
        case PNM_GRE_BINARY: return read_pnm_gray_binary_data(f, b);
        case PNM_PIX_BINARY: return read_pnm_pix_binary_data(f, b);
    }

    return -1;
}


// --- Writers
static
int write_pnm_bit_ascii_data(FILE * f, const int * b, int w, int h) {
    int r = 0;

    for (int i = 0; i < w*h; i++) {
        r += fprintf(f, "%d ", b[i]);
        if ((i + 1) % w == 0) {
            r += fputc('\n', f);
        }
    }

    return r;
}

static
int write_pnm_bit_binary_data(FILE * f, const int * b, int w, int h) {
    int r = 0;

    for (int i = 0; i < w*h; i++) {
        int v = 0;
        for (int h = 0; h < 8; h++) {
            v |= (b[i] << (7-h));
        }
        r += fputc('0' + v, f);
    }

    return 1;
}

static
int write_pnm_gray_ascii_data(FILE * f, const int * b, int w, int h) {
    return write_pnm_bit_ascii_data(f, b, w, h);
}

static
int write_pnm_gray_binary_data(FILE * f, const int * b, int w, int h) {
    int r = 0;

    for (int i = 0; i < w*h; i++) { r += fprintf(f, "%c", b[i]); }

    return r;
}

static
int write_pnm_pix_ascii_data(FILE * f, const int * b, int w, int h) {
    int r = 0;

    for (int i = 0; i < w*h; i++) {
        r += fprintf(f, "%d %d %d  ", 
            b[0], 
            b[1], 
            b[2]
        );
        b += 3;
        if ((i + 1) % w == 0) {
            fprintf(f, "\n");
        }
    }

    return r;
}

static
int write_pnm_pix_binary_data(FILE * f, const int * b, int w, int h) {
    return write_pnm_gray_binary_data(f, b, w*3, h);
}

int write_pnm_file(FILE * f, pnm_type_t type, const int * b, int w, int h, int intensity) {
    int r = 0;

    char magic[] = "PX";
    magic[1] = '0' + type;
    r += fputs(magic, f);

    if (type == PNM_BIT_ASCII
    ||  type == PNM_BIT_BINARY) {
        r += fprintf(f, "\n%d %d\n", w, h);
    } else {
        r += fprintf(f, "\n%d %d %d\n", w, h, intensity);
    }

    switch (type) {
        case PNM_BIT_ASCII:  r += write_pnm_bit_ascii_data   (f, b, w, h); break;
        case PNM_GRE_ASCII:  r += write_pnm_gray_ascii_data  (f, b, w, h); break;
        case PNM_PIX_ASCII:  r += write_pnm_pix_ascii_data   (f, b, w, h); break;
        case PNM_BIT_BINARY: r += write_pnm_bit_binary_data  (f, b, w, h); break;
        case PNM_GRE_BINARY: r += write_pnm_gray_binary_data (f, b, w, h); break;
        case PNM_PIX_BINARY: r += write_pnm_pix_binary_data  (f, b, w, h); break;
    }

    return r;
}
