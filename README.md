# Libchad
> Who said you ought to reinvent the wheel?

---

## Rationele
C libraries are hard to find; good libraries are even harder.

## Contents

> [!NOTE] `chad.h` includes all Chad libraries.

### IO

| Lib         | Description |
| :---        | :---------- |
| dictate.h   | Über-printer. |
| plumblism.h | PBMplus (PNM) image IO. |

### Datastructures

| Lib    | Description |
| :---   | :---------- |
| sds.h  | Dynamic strings. |

### Ported functionality

| Lib           | Lang  | Description |
| :---          | :---: | :---------- |
| qx.h          | Perl  | Capture output of exec. |
| remove\_all.h | C++   | Remove a directory recursively. |

---

## Experimental
The mainline chad libraries are considered to have a stable API.
They might get extended, but are not expected to change.
Experimental libraries on the other hand are volatile.

| Lib    | Description |
| :---   | :---------- |
| bits.h | Various miscellaneous functionalities. |
| kvec.h | Small, typesafe, generic datastructures optimized for speed. |

## Criteria

* A clear way in which the functionality can be described as.
(e.g.: "generic datastructures" - good; "roguelike stuff" - bad)
* Clean and simple interface which can be learned under a few minutes.
Complexity has its place: within its own library.
* Must be amalgamable into a single header.
* No project-namespacing.

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
    file arena.h {
        arena_t new_arena(size_t n_bytes);
        void * arenaloc(arena_t * a, size_t n_bytes);
        int free_arena(arena_t * a);
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
    # trim() and pad() even tho its a meme
    # MB(n) etc. macros
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
    # Same applies to plan9
    # * libutf
```
