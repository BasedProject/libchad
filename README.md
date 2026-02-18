# Libchad
> Who said you ought to reinvent the wheel?

---

## Rationele
C libraries are hard to find; good libraries are even harder.
Libchad is a collection of quality, general-purpose, high-level libraries
aimed at modern C development.

## Compatibility
Libchad is standard C23.
Individual components might be compatible with older standards.

Headers must compile under C++17[^cpp].

Linux is the primary target OS[^target],
however compatibility with other UNIX-like operating systems should also be considered.
Compatibility with Windows is NOT a concern.

[^target]: This might be subject to change in the future,
particularly to BSD when the Linux finally becomes too tightly integrated with cancerware,
such as Rust and Systemd.

[^cpp]: This requirement added for practicality.
It might be subject to change specifically
if some meta-programming based OOP solution for C
gains appropriate maturity.

## Contents

> [!NOTE] `chad.h` includes all Chad libraries.

### IO

| Lib         | Description |
| :---        | :---------- |
| dictate.h   | Über-printer. |
| plumblism.h | PBMplus (PNM) image IO. |
// https://github.com/ClecioJung/ini (slight renaming and _Generic)
// https://github.com/an-dr/microlog

### Datastructures

| Lib       | Description |
| :---      | :---------- |
| sds.h     | Dynamic strings. |
| haste.h   | Type-safe generic containers optimized single threaded speed. |
| strlist.h | String lists. |

### Memory

| Lib            | Description |
| :---           | :---------- |
| memory-units.h | Memory unit macros. |
| zone.h         | Zone allocator. |
// arena allocator

### Ported functionality

| Lib           | Lang  | Description |
| :---          | :---: | :---------- |
| qx.h          | Perl  | Capture output of exec. |
| slurp.h       | Perl  | Simple reading/writing/modifying of complete files. |
| remove\_all.h | C++   | Remove a directory recursively. |

---

## Experimental
The mainline chad libraries are considered to have a stable API.
They might get extended, but are not expected to change.
Experimental libraries on the other hand are volatile.

| Lib    | Description |
| :---   | :---------- |
| bits.h | Various miscellaneous functionalities. |

## Criteria
* A clear way in which the functionality can be described as.
(e.g.: "generic datastructures" - good; "roguelike stuff" - bad)
* Clean and simple interface which can be learned under a few minutes.
Complexity has its place: within its own library.
* Must be amalgamable into a single header.
* No project-namespacing.
* The top of the headers must have a *description comment*.
* The *description comment* must be followed by declarations.
* License comments may not take up more than 3 lines (worst case being a title, the license body and the list of people holding the copyright).
* Each library must come with a `man(1)` compatible manual.

## Recommendations
Some subjects are outside of the scope of this project,
but not outside of its interest.
For such cases, a recommendations table exists.
Any item on the recommendations table have been throughly reviewed
and is believed to be the best-of-its-kind as of now.
Consequently, only one item per subject should be provided
and a clean-cut predicate to choose between items of similar subjects.

| Library | Subject | Description |
| :------ | :------ | :---------- |
| XXX | XXX | XXX |

## Todo
* peru is nice as a concept, but 1) depends on py-yaml, 2) yaml makes make me vomit from my eyes
* code
```sh
    file filesystem.h {
        int touch_file(const char * p);
        int touch_directory(const char * p);
        int touch(const char * p);  // wrapper based on whether the last char is '/'

        int copy_file(const char * s, const char * d);
        int copy(const char * s, const char * d);
        int copy_ex(const char * s, const char * d, int flags);

        int remove(const char * p);
        int remove_all(const char * p);

        int rename(const char * s, const char * d);
    }
    tree chad/
        file nargs.h { // for narg hack functions?
            #define coalesce_env() // char * _coalesce_env(char * mydefault, size_t argc, ...)
            // maybe just coalesce()? that means every argument is eval-ed; maybe both
            #define max()
            #define min()
            // all(), any() 
            // ?! i cant think of a single instance where its preferable over plain logic,
            //  but it would be consistent
        }
    # something addressing math.h
    #  gcd(), lcm(), sq() /*square, after ino*/
    #
    # the linux kernel has a bunch of small, high quality utilities,
    #  these should be inspected
    # * minmax.h looks good; i wonder if it can be made N-arg
    #    in_range does not with in _there_
    # * array_size.h looks good
    # * DIV_ROUND_UP
    # * base64.h
    # * crc?
    # * glob.h
    #
    # Strings:
    #   trim() and pad() even tho its a meme
    #   slugify
    #   reverse
    #   case conversions
```

The following items should be considered to be added to libchad, in some way or another:
+ [ ] Xandard
+ [ ] Plan9 (e.g. libutf)
+ [ ] [https://github.com/EasyMem/easy_memory](https://github.com/EasyMem/easy_memory)
+ [ ] [https://github.com/tarantula-org/camelot](https://github.com/tarantula-org/camelot)
+ [ ] [https://www.gnu.org/software/gnulib/manual/html_node/index.html](https://www.gnu.org/software/gnulib/manual/html_node/index.html)
+ [ ] [https://github.com/arp242/toml-c](https://github.com/arp242/toml-c)
+ [ ] [https://github.com/wolkykim/qlibc](https://github.com/wolkykim/qlibc) (qencode, qcount)
+ [ ] [https://github.com/swansontec/map-macro](https://github.com/swansontec/map-macro)
+ [ ] [https://www.boost.org/doc/libs/latest/libs/preprocessor/doc/index.html](https://www.boost.org/doc/libs/latest/libs/preprocessor/doc/index.html)
+ [ ] [https://github.com/ClecioJung/ini](https://github.com/ClecioJung/ini)
+ [ ] [https://github.com/arp242/toml-c](https://github.com/arp242/toml-c)
+ [ ] [https://git.enlightenment.org/enlightenment/efl](https://git.enlightenment.org/enlightenment/efl)
+ [ ] [https://github.com/scottt/debugbreak.git](https://github.com/scottt/debugbreak.git) (since the compatibility is a nightmare, maybe just provide `breakpoint()`, which is empty, but kept from being optimized away)
