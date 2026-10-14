/* dedent.h
 *
 * > single-header leading whitespace removal library
 *
 * Usage:
 *   #define DEDENT_IMPLEMENTATION
 *   #include "dedent.h"
 *
 * Requires C23.
 */
#ifndef DEDENT_H_INCLUDED
#define DEDENT_H_INCLUDED

#include <sys/types.h>

/* Returns the number of common leading whitespace characters.
 *   >  0  : the common indent width, in characters.
 *   == 0  : no common indent (also returned for NULL/empty/all-blank `s`).
 *   == -1 : leading whitespace mixes ' ' and '\t'
 *
 * Blank lines and whitespace-only lines are ignored.
 */
[[nodiscard]] ssize_t get_indent_width(const char * s);

/* Returns `s` with the common leading whitespace removed.
 * 
 * Returns nullptr before modifying `s` if ' ' and '\t' are mixed.
 *
 * Whitespace-only lines are stripped to `\n`.
 */
char * dedent(char * s);

#endif

/* ------------------------------------------------------------------ */

#ifdef DEDENT_IMPLEMENTATION
#ifndef DEDENT_IMPLEMENTATION_ONCE
#define DEDENT_IMPLEMENTATION_ONCE

#include <limits.h>
#include <stddef.h>

[[nodiscard]]
ssize_t get_indent_width(const char * const s) {
    if (!s
    ||  !s[0]) {
        return 0;
    }

    bool has_space = false;
    bool has_tab   = false;
    ssize_t current_leading_space = 0;
    ssize_t r = SSIZE_MAX;

    enum {
        STATE_BEGINNING_OF_LINE,
        STATE_FIND_BEGINNING_OF_LINE,
        STATE_EAT_NEW_LINES,
    } state = STATE_EAT_NEW_LINES;

    for (size_t i = 0; s[i] != '\0'; i++) {
        switch (state) {
            case STATE_EAT_NEW_LINES: {
                switch (s[i]) {
                    case '\n': break;
                    default: {
                        --i;
                        state = STATE_BEGINNING_OF_LINE;
                    } break;
                }
            } break;
            case STATE_BEGINNING_OF_LINE: {
                switch (s[i]) {
                    case ' ': {
                        has_space = true;
                        if (has_tab) {
                            return -1;
                        }
                       ++current_leading_space;
                    } break;
                    case '\t': {
                        has_tab = true;
                        if (has_space) {
                            return -1;
                        }
                        ++current_leading_space;
                    } break;
                    case '\n': {
                        current_leading_space = 0;
                        state = STATE_EAT_NEW_LINES;
                    } break;
                    default: {
                        if (r > current_leading_space) {
                            r = current_leading_space;
                        }
                        current_leading_space = 0;
                        state = STATE_FIND_BEGINNING_OF_LINE;
                    } break;
                }
            } break;
            case STATE_FIND_BEGINNING_OF_LINE: {
                switch (s[i]) {
                    case '\n': {
                        state = STATE_EAT_NEW_LINES;
                    } break;
                    default: break;
                }
            } break;
        }
    }
    return r == SSIZE_MAX ? 0 : r;
}

char * dedent(char * const s) {
    if (!s) {
        return nullptr;
    }
    if (!s[0]) {
        return s;
    }

    ssize_t const strip = get_indent_width(s);
    if (strip < 0) {
        return nullptr;
    }

    ssize_t out_cursor = 0;
    ssize_t leading_space_on_line = 0;
    enum {
        STATE_SKIP_LEADING_WHITESPACE,
        STATE_COPY_LINE,
    } state = STATE_SKIP_LEADING_WHITESPACE;
    for (ssize_t in_cursor = 0; s[in_cursor] != '\0'; in_cursor++) {
        switch (state) {
            case STATE_SKIP_LEADING_WHITESPACE: {
                switch (s[in_cursor]) {
                    case ' ':
                    case '\t': {
                        ++leading_space_on_line;
                    } break;
                    case '\n': {
                        s[out_cursor++] = s[in_cursor];
                        leading_space_on_line = 0;
                    } break;
                    default: {
                        in_cursor += strip - leading_space_on_line - 1;
                        leading_space_on_line = 0;
                        state = STATE_COPY_LINE;
                    } break;
                }
            } break;
            case STATE_COPY_LINE: {
                switch (s[in_cursor]) {
                    case '\n': {
                        s[out_cursor++] = s[in_cursor];
                        state = STATE_SKIP_LEADING_WHITESPACE;
                    } break;
                    default: {
                        s[out_cursor++] = s[in_cursor];
                    } break;
                }
            } break;
        }
    }
    s[out_cursor] = '\0';
    return s;
}

#endif
#endif
