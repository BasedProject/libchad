# Libchad
> Who said you ought to reinvent the wheel?

---

## Rationale
C libraries are hard to find; good libraries are even harder.

Libchad is a collection of quality, general-purpose, high-level libraries
aimed at modern C development.

## Install

```sh
PREFIX=/usr make install
```

This will provide you with <terry.h> (for fundamental basic types)
and <chad/...> (which is for everything else.)

## Status

This library is not complete, but that does not mean it is not ready for usage.

You are free to package this into whatever you wish under the terms of SPDX:MPL-2.0.
Note that some subware here may have more permissive licensing, such as Public Domain or MIT.

You can assume that all source here is at least under MPL-2.0:
* If you distribute modified versions of the library, you are required to make the modified source available.
* You may link this software statically without affecting the license of your own code.
* You must include a copy of the MPL-2.0 license.

## Compatibility
Libchad will only support C23.
Individual components might be compatible with older standards,
though this is not expected and not wanted.

Headers must compile under C++17[^cpp].

Linux is the primary target OS[^target],
however compatibility with other UNIX-like operating systems should also be considered.
Compatibility with Windows is NOT a concern.

[^target]: This will likely remain Linux for a long time.
Windows support is actively NOT SUPPORTED.
BSD will, at somepoint, be supported and may be become the fundamental of this library.
MacOS would be reasonable under conditions of minor changes only.

[^cpp]: This requirement added for practicality.
It might be subject to change specifically if some meta-programming based OOP solution for C gains appropriate maturity.
Support for this may be shakey and is not tested at this instant.

## Criteria

Strong requirements:
* A clear, general purpose. (e.g.: "generic datastructures" - good; "roguelike stuff" - bad)
* Clean and simple interface which can be learned under a few minutes. Complexity has its place: within its own library.
* No inlined project-namespacing.
* Code must be licensed under weak copyleft (ensures librarying in any software is permitted) or permissive.

Longterm, less important requirements:
* Must be amalgamable into a single header.
* Useful comment data:
- Individual headers must have a *description comment*.
- The *description comment* must be followed by declarations.
* Licenses must use their SPDX License Identifiers (e.g.: SPDX:GPL-3.0-or-later).
* Each library must come with a `man(1)` compatible manual.

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
| chad/haste.h   | Type-safe generic containers optimized single threaded speed. |
| chad/sds.h     | Dynamic strings. |
| chad/strlist.h | String lists. |
| chad/terry.h & terry.h | Fundamental. |

### Memory

| Lib            | Description |
| :---           | :---------- |
| chad/memory-units.h | Memory unit macros. |
| chad/zone.h         | Zone allocator. |
// arena allocator

### Ported functionality

| Lib           | Lang  | Description |
| :---          | :---: | :---------- |
| chad/XXX.h         | Perl  | Macro to mark unimplemented code. |
| chad/qx.h          | Perl  | Capture output of exec. |
| chad/remove\_all.h | C++   | Remove a directory recursively. |
| chad/slurp.h       | Perl  | Simple reading/writing/modifying of complete files. |

### XXX

| Lib      | Description |
| :---     | :---------- |
| chad/bits.h   | Various miscellaneous functionalities. |
| chad/dyrect.h | Rectangle layout utility box. |
| chad/random/random.h | Provides various randomizers, see <https://github.com/Basedproject/librandom> for details. |
| chad/roman.h  | Convert to and from roman numerals. |

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
* peru is FINE as is. Could be improved but there's no need. Peru is not explicitly required in the build.
* SO MUCH SHIT IS MISSING FROM THE LIBRARY WHAT THE HELL
- /* #include "chad/XXX.h" */
- /* #include "chad/dyrect.h" */
- /* #include "chad/roman.h" */
- experimental/ro.h should be destroyed from space
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
    #   chomp
    #
    # raylib math util:
    #  float Clamp(float value, float min, float max);                             // Clamp float value
    #  float Lerp(float start, float end, float amount);                           // Calculate linear interpolation between two floats
    #  float Normalize(float value, float start, float end);                       // Normalize input value within input range
    #  float Remap(float value, float inputStart, float inputEnd, float outputStart, float outputEnd); // Remap input value within input range to output range
    #  float Wrap(float value, float min, float max);                              // Wrap input value from min to max
    #
    # a slab allocator
    #
    # timeouts
    #
    # colors (../libcolor/)
    #
    # roman numbers
    #
    # the number parsing functions of the standard are shit
    #   unsigned parsing wraps, because fuck you
    #   they require null terminated strings
    #
    # spinners?
    #
    # dedent?
    #
    # lliffe arrays
```

The following items should be considered to be added to libchad, in some way or another:
+ [ ] Xandard
+ [ ] Plan9 (e.g. libutf)
+ [ ] [https://github.com/EasyMem/easy_memory](https://github.com/EasyMem/easy_memory)
+ [ ] [https://github.com/tarantula-org/camelot](https://github.com/tarantula-org/camelot)
+ [ ] [https://www.gnu.org/software/gnulib/manual/html_node/index.html](https://www.gnu.org/software/gnulib/manual/html_node/index.html)
+ [ ] [https://github.com/wolkykim/qlibc](https://github.com/wolkykim/qlibc) (qencode, qcount)
+ [ ] [https://github.com/swansontec/map-macro](https://github.com/swansontec/map-macro)
+ [ ] [https://www.boost.org/doc/libs/latest/libs/preprocessor/doc/index.html](https://www.boost.org/doc/libs/latest/libs/preprocessor/doc/index.html)
+ [ ] [https://github.com/ClecioJung/ini](https://github.com/ClecioJung/ini)
+ [ ] [https://github.com/arp242/toml-c](https://github.com/arp242/toml-c)
+ [ ] [https://github.com/EldoDebug/fastoml](https://github.com/EldoDebug/fastoml)
+ [ ] [https://git.enlightenment.org/enlightenment/efl](https://git.enlightenment.org/enlightenment/efl)
+ [ ] [https://github.com/scottt/debugbreak.git](https://github.com/scottt/debugbreak.git) (since the compatibility is a nightmare, maybe just provide `breakpoint()`, which is empty, but kept from being optimized away)
+ [ ] [https://gitlab.freedesktop.org/libbsd/](https://gitlab.freedesktop.org/libbsd/) (vis)
+ [ ] [https://github.com/kdslfjioasdfj/clib2/tree/main/include](https://github.com/kdslfjioasdfj/clib2/tree/main/include) (404)
+ [ ] [https://github.com/managarm/mlibc] (https://github.com/managarm/mlibc)
+ [ ] [https://github.com/floooh/sokol] (https://github.com/floooh/sokol)
