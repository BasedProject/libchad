#ifndef STRLIST_H
#define STRLIST_H

/* The string based list is a common pattern,
 *  as it is the most intuitive way to serialize a list.
 *
 * In many languages you would handle it by instantiating
 *  an actual list by means of splitting,
 *  but in C we can often do better
 *  (and we dont have general lists to begin with).
 *
 * Examples would include:
 *  + file paths (a/b)
 *  + file extensions (a.b)
 *  + unix style option lists (a:b)
 *  + symbol hierarchies (a->b)
 */

typedef const char * const * const sep_t;
sep_t UNIX_PATH_SEP = { "/", NULL, };
sep_t DOS_PATH_SEP  = { "\\", NULL, };
sep_t UNIX_SEP      = { ":", NULL, };
sep_t CPP_SEP       = { "::", ".", "->", NULL, };
sep_t EXT_SEP       = { ".", NULL, };

size_t strlist_len(char * list, sep_t sep);

/* This function in an abstract sense performs list indexing.
 *  The result overwrites the `list` argument and is returned.
 *  (We know that this may never result in an overflow.)
 */
char * strlist_component(char * list, size_t n, sep_t sep);
/* This function returns a range.
 */
char * strlist_components(char * list, size_t from, size_t to, sep_t sep);

/* The following are shorthands for component()/components(),
 *  with a specific numbers which may or may not be length specific
 *
 * Visual explanation:
 *       this/is/my/example/path
 *  Root <---------------->
 *  Base                    <-->
 *  Head <-->
 *  Tail      <---------------->
 */
char * strlist_root(char * list, sep_t sep);
char * strlist_base(char * list, sep_t sep);
char * strlist_head(char * list, sep_t sep);
char * strlist_tail(char * list, sep_t sep);

/* Notes:
 *  + we very consciously made the decision to not take a destination operand;
 *     you would have to allocate it just the same,
 *     copying the source string is not a real performance concern,
 *     but we want our interface to be as clean as possible
 */

/* Example:
 *  Getting the absolute basename of a file.
 *      char name[] = "this/is/my.file.example";
 *      name = strlist_head(strlist_base(name, UNIX_PATH_SEP), EXT_SEP);
 */

#endif
