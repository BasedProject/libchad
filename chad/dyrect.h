#ifndef DYRECT_H
#define DYRECT_H
/* This header file defines with intuitive rectangle transformations.
 *
 * The intended purpose is to ease defining single screen interfaces.
 *  Layout engines are great, but very complex to implement and master.
 *  Static layouts on the other hand tend to get very ugly, verbose and bug prone.
 *  The idea is to have a very minimalistic abstraction layer,
 *   with easy to visualize operations.
 *  This solves readability and typo-ing x to y, while being widely usable,
 *   adaptable or even reimplementable within just a few minutes.
 *
 * No doubt someone somewhere has adapted a similar approach before,
 *  however to the best of my knowledge this is the first attempt
 *  to normalize it into a library.
 *  In case I'm wrong, please throw me an email. (agvxov@gmail.com)
 */

// TODO: reach is hard to conceptulize
// TODO: scale is somewhat redundant

/* Dyrect can use an arbitrary C style namespace,
 *  or use the prefix `dr_` if the following feature macro is requested.
 */
#ifdef DYRECT_DO_NAMESPACE
# ifndef DYRECT_PREFIX
#  define DYRECT_PREFIX(s) dr_ ## s
# endif
#else
# define DYRECT_PREFIX(s) s
#endif


// ### --------------- ###
// ### SPECIALIZATIONS ###
// ### --------------- ###
/* This has to go on top, because macros. Please read on.
 */

#ifdef RAYLIB_H
# define rect_t Rectangle
# define w width
# define h height
static inline
rect_t DYRECT_PREFIX(get_screen_rect)(void) {
    return (rect_t) {
        .x = 0,
        .y = 0,
        .w = (float)GetScreenWidth(),
        .h = (float)GetScreenHeight(),
    };
}
#endif


// ### ------- ###
// ### General ###
// ### ------- ###

/* Our internal rectangle representation.
 *  Feel free to overwrite it with whatever suits you,
 *   just #define alias it to `rect_t`.
 */
#ifndef rect_t
typedef struct rect_t {
    float x, y, w, h;
} rect_t;
#endif

#ifndef x
# define x x
#endif
#ifndef y
# define y y
#endif
#ifndef w
# define w w
#endif
#ifndef h
# define h h
#endif

#ifdef __NCURSES_H
# define DNUNPACK(r) (int)r.h, (int)r.w, (int)r.y, (int)r.x
static inline
rect_t DYRECT_PREFIX(get_screen_rect)(void) {
    return (rect_t) {
        .x = 0,
        .y = 0,
        .w  = (float)COLS,
        .h = (float)LINES,
    };
}
#endif

// # TL;DR
// Utility
/* Return a rect with one or more properties operated on arbitrarily.
 * Examples:
 *   dyrect(r, +4, +0, +0, +0) // Move to the right by 4 units; pass unused explicitly
 *   dyrect(r, , , *2, *2)     // Scale a rectangle by 2; pass unused implicitly
 */
#define dyrect(r, a, b, c, d) ( \
    (rect_t) {                  \
        .x = r.x a,             \
        .y = r.y b,             \
        .w = r.w c,             \
        .h = r.h d,             \
    }\
)
static inline rect_t DYRECT_PREFIX(rfloor)(rect_t r);
static inline rect_t DYRECT_PREFIX(get_unit_rect)(void);
/*                   DYRECT_PREFIX(get_screen_rect)(void); // only when known library is detected */
// Resizing
static inline rect_t DYRECT_PREFIX(scalex)(rect_t a, float f);
static inline rect_t DYRECT_PREFIX(scaley)(rect_t a, float f);
static inline rect_t DYRECT_PREFIX(scalexy)(rect_t a, float fw, float fh);
static inline rect_t DYRECT_PREFIX(scale)(rect_t a, float f);
static inline rect_t DYRECT_PREFIX(growx)(rect_t a, float f);
static inline rect_t DYRECT_PREFIX(growy)(rect_t a, float f);
static inline rect_t DYRECT_PREFIX(growxy)(rect_t a, float fw, float fh);
static inline rect_t DYRECT_PREFIX(grow)(rect_t a, float f);
// Absolute Moving
static inline rect_t DYRECT_PREFIX(rail_step)(rect_t source, int n);
static inline rect_t DYRECT_PREFIX(rope_step)(rect_t source, int n);
// Relative Moving
static inline rect_t DYRECT_PREFIX(inner_up)(rect_t dest, rect_t source);
static inline rect_t DYRECT_PREFIX(inner_down)(rect_t dest, rect_t source);
static inline rect_t DYRECT_PREFIX(inner_left)(rect_t dest, rect_t source);
static inline rect_t DYRECT_PREFIX(inner_right)(rect_t dest, rect_t source);
static inline rect_t DYRECT_PREFIX(outer_up)(rect_t dest, rect_t source);
static inline rect_t DYRECT_PREFIX(outer_down)(rect_t dest, rect_t source);
static inline rect_t DYRECT_PREFIX(outer_left)(rect_t dest, rect_t source);
static inline rect_t DYRECT_PREFIX(outer_right)(rect_t dest, rect_t source);
static inline rect_t DYRECT_PREFIX(balance)(rect_t dest, rect_t source);
static inline rect_t DYRECT_PREFIX(buoyance)(rect_t dest, rect_t source);
static inline rect_t DYRECT_PREFIX(center)(rect_t dest, rect_t source);
// ???
static inline rect_t DYRECT_PREFIX(reachy)(rect_t dest, rect_t source);
static inline rect_t DYRECT_PREFIX(reachx)(rect_t dest, rect_t source);



/* Floor every field of a rect.
 *  Useful if next() or after() create visible gaps.
 *  NOTE: we are not actually flooring so we dont depend on <math.h>,
 *         for our ends and purposes it should just werk™
 */
static inline
rect_t DYRECT_PREFIX(rfloor)(rect_t r) {
    return (rect_t) {
        .x = (float)(long long)r.x,
        .y = (float)(long long)r.y,
        .w = (float)(long long)r.w,
        .h = (float)(long long)r.h,
    };
}


/* Return the easiest rect to transform.
 *  Coordinates (0, 0) are easy to shift.
 *  Size 1x1 is easy to scale.
 * 
 *   +-+
 *   +-+
 */
static inline
rect_t DYRECT_PREFIX(get_unit_rect)(void) {
    return (rect_t) {
        .x = 0,
        .y = 0,
        .w = 1,
        .h = 1,
    };
}


/* Modify the w by a factor.
 *
 *   +-+   __\  +---+
 *   +-+     /  +---+
 */
static inline
rect_t DYRECT_PREFIX(scalex)(rect_t a, float f) {
    return (rect_t) {
        .x = a.x,
        .y = a.y,
        .w = a.w  * f,
        .h = a.h,
    };
}


/* Modify the h by a factor.
 *
 *   +-+   __\  +-+
 *   +-+     /  | |
 *              +-+
 */
static inline
rect_t DYRECT_PREFIX(scaley)(rect_t a, float f) {
    return (rect_t) {
        .x = a.x,
        .y = a.y,
        .w = a.w,
        .h = a.h * f,
    };
}

/* Modify the h and w by different factors.
 *
 *   +-+   __\  +---+
 *   +-+     /  |   |
 *              +---+
 */
static inline
rect_t DYRECT_PREFIX(scalexy)(rect_t a, float fw, float fh) {
    return (rect_t) {
        .x = a.x,
        .y = a.y,
        .w = a.w  * fw,
        .h = a.h * fh,
    };
}

/* Modify the h and w by the same factor.
 *
 *   +-+   __\  +---+
 *   +-+     /  |   |
 *              +---+
 */
static inline
rect_t DYRECT_PREFIX(scale)(rect_t a, float f) {
    return (rect_t) {
        .x = a.x,
        .y = a.y,
        .w = a.w  * f,
        .h = a.h * f,
    };
}

/* Modify the w by a factor, while not moving the center point.
 *   +---+---+---+
 *   | < |   | > |
 *   +---+---+---+
 */
static inline
rect_t DYRECT_PREFIX(growx)(rect_t a, float f) {
    return (rect_t) {
        .x = a.x + (a.w - (a.w * f)) * 0.5,
        .y = a.y,
        .w = a.w * f,
        .h = a.h,
    };
}

/* Modify the h by a factor, while not moving the center point.
 *   +---+
 *   | ^ |
 *   | ^ |
 *   +---+
 *   |   |
 *   +---+
 *   | v |
 *   | v |
 *   +---+
 */
static inline
rect_t DYRECT_PREFIX(growy)(rect_t a, float f) {
    return (rect_t) {
        .x = a.x,
        .y = a.y + (a.h - (a.h * f)) * 0.5,
        .w = a.w,
        .h = a.h * f,
    };
}

/* Modify the w and h by factors, while not moving the center point.
 *   +-+---+-+
 *   |   ^   |
 *   |   ^   |
 *   + +---+ +
 *   |<|   |>|
 *   + +---+ +
 *   |   v   |
 *   |   v   |
 *   +-+---+-+
 */
static inline
rect_t DYRECT_PREFIX(growxy)(rect_t a, float fw, float fh) {
    return (rect_t) {
        .x = a.x + (a.w  - (a.w  * fw)) * 0.5,
        .y = a.y + (a.h - (a.h * fh)) * 0.5,
        .w = a.w  * fw,
        .h = a.h * fh,
    };
}

/* Modify the w and h by a factor, while not moving the center point
 *   +---------+
 *   |    A    |
 *   |  +---+  |
 *   |< |   | >|
 *   |  +---+  |
 *   |    v    |
 *   +---------+
 */
static inline
rect_t DYRECT_PREFIX(grow)(rect_t a, float f) {
    return (rect_t) {
        .x = a.x + (a.w  - (a.w * f))  * 0.5,
        .y = a.y + (a.h - (a.h * f)) * 0.5,
        .w = a.w  * f,
        .h = a.h * f,
    };
}

/* Align to the middle horizontally.
 *
 *   +---+---+---+
 *   |   |   |   |
 *   | - |   | - |
 *   |   +---+   |
 *   |           |
 *   |           |
 *   |           |
 *   +---+---+---+
 */
static inline
rect_t DYRECT_PREFIX(balance)(rect_t dest, rect_t source) {
    return (rect_t) {
        .x = dest.x + ((dest.w - source.w) / 2),
        .y = source.y,
        .w = source.w,
        .h = source.h,
    };
}

/* Align to the middle vertically.
 *
 *   +---+---+---+
 *   | :         |
 *   +---+       |
 *   |   |       |
 *   |   |       |
 *   +---+       |
 *   | :         |
 *   +---+---+---+
 */
static inline
rect_t DYRECT_PREFIX(buoyance)(rect_t dest, rect_t source) {
    return (rect_t) {
        .x = source.x,
        .y = dest.y + ((dest.h - source.h) / 2),
        .w = source.w,
        .h = source.h,
    };
}


/* Balance and Buoyance. Align to the middle vertically and horizontally.
 *
 *   +-----------+
 *   |     :     |
 *   |   +---+   |
 *   | - |   | - |
 *   |   |   |   |
 *   |   +---+   |
 *   |     :     |
 *   +-----------+
 */
static inline
rect_t DYRECT_PREFIX(center)(rect_t dest, rect_t source) {
    return balance(dest, buoyance(dest, source));
}


/* Dangles from the top.
 *
 *   +-+---+-----+
 *   | |   |     |
 *   | |   |     |
 *   | +---+     |
 *   |           |
 *   |           |
 *   |           |
 *   +-----------+
 */
static inline
rect_t DYRECT_PREFIX(inner_up)(rect_t dest, rect_t source) {
    return (rect_t) {
        .x = source.x,
        .y = dest.y,
        .w = source.w,
        .h = source.h,
    };
}

/* Dangles from the bottom.
 *
 *   +-----------+
 *   |           |
 *   |           |
 *   |           |
 *   |     +---+ |
 *   |     |   | |
 *   |     |   | |
 *   +-----+---+-+
 */
static inline
rect_t DYRECT_PREFIX(inner_down)(rect_t dest, rect_t source) {
    return (rect_t) {
        .x = dest.x,
        .y = dest.y + dest.h - source.h,
        .w = source.w,
        .h = source.h,
    };
}

/* Dangles from the left.
 *
 *   +-----------+
 *   |           |
 *   |           |
 *   +---+       |
 *   |   |       |
 *   |   |       |
 *   +---+       |
 *   +-----------+
 */
static inline
rect_t DYRECT_PREFIX(inner_left)(rect_t dest, rect_t source) {
    return (rect_t) {
        .x = dest.x,
        .y = source.y,
        .w = source.w,
        .h = source.h,
    };
}

/* Dangles from the right.
 *
 *   +-----------+
 *   |       +---+
 *   |       |   |
 *   |       |   |
 *   |       +---+
 *   |           |
 *   |           |
 *   +-----------+
 */
static inline
rect_t DYRECT_PREFIX(inner_right)(rect_t dest, rect_t source) {
    return (rect_t) {
        .x = dest.x + dest.w - source.w,
        .y = source.y,
        .w = source.w,
        .h = source.h,
    };
}

/* Places on the top.
 *
 *   +---+
 *   |   |
 *   |   |
 *   +---+-------+
 *   |           |
 *   |           |
 *   |           |
 *   |           |
 *   |           |
 *   |           |
 *   +-----------+
 */
static inline
rect_t DYRECT_PREFIX(outer_up)(rect_t dest, rect_t source) {
    return (rect_t) {
        .x = source.x,
        .y = dest.y - source.h,
        .w = source.w,
        .h = source.h,
    };
}

/* Places on the bottom.
 *
 *   +-----------+
 *   |           |
 *   |           |
 *   |           |
 *   |           |
 *   |           |
 *   |           |
 *   +---+-------+
 *   |   |
 *   |   |
 *   +---+
 */
static inline
rect_t DYRECT_PREFIX(outer_down)(rect_t dest, rect_t source) {
    return (rect_t) {
        .x = source.x,
        .y = dest.y + dest.h,
        .w = source.w,
        .h = source.h,
    };
}

/* Places on the left.
 *
 *   +---+-----------+
 *   |   |           |
 *   |   |           |
 *   +---+           |
 *       |           |
 *       |           |
 *       |           |
 *       +-----------+
 */
static inline
rect_t DYRECT_PREFIX(outer_left)(rect_t dest, rect_t source) {
    return (rect_t) {
        .x = dest.x - source.w,
        .y = source.y,
        .w = source.w,
        .h = source.h,
    };
}

/* Places on the right.
 *
 *   +-----------+---+
 *   |           |   |
 *   |           |   |
 *   |           +---+
 *   |           |
 *   |           |
 *   |           |
 *   +-----------+
 */
static inline
rect_t DYRECT_PREFIX(outer_right)(rect_t dest, rect_t source) {
    return (rect_t) {
        .x = dest.x + dest.w,
        .y = source.y,
        .w = source.w,
        .h = source.h,
    };
}

/* Gets the N-th horizontal neighbour.
 *
 *   +---+---+
 *   |   |   |
 *   |   |   |
 *   +---+---+
 */
static inline
rect_t DYRECT_PREFIX(rail_step)(rect_t source, int n) {
    return (rect_t) {
        .x = source.x + (source.w * n),
        .y = source.y,
        .w = source.w,
        .h = source.h,
    };
}

/* Gets the N-th vertical neighbour.
 *
 *   +---+    
 *   |   |
 *   |   |
 *   +---+
 *   |   |
 *   |   |
 *   +---+
 */
static inline
rect_t DYRECT_PREFIX(rope_step)(rect_t source, int n) {
    return (rect_t) {
        .x = source.x,
        .y = source.y + (source.h * n),
        .w = source.w,
        .h = source.h,
    };
}

/* Make the closest opposite facing vertical edges touch.
 *  or fill the destination vectically.
 *                          ||| 
 *   +--+          +--+     ||| 
 *   |  |          |  |     |||   +------+       +-+--+-+
 *   +--+          |  |     |||   | +--+ |  __\  | |  | |
 *           __\   |  |     |||   | +--+ |    /  | |  | |
 *     +--+    /   +--+-+   |||   +------+       +-+--+-+
 *     |  |          |  |   ||| 
 *     +--+          +--+   ||| 
 */
static inline
rect_t DYRECT_PREFIX(reachy)(rect_t dest, rect_t source) {
    return (dest.y > source.y) ?
        (rect_t) {
            .x = source.x,
            .y = source.y,
            .w = source.w,
            .h = dest.y - source.y,
        }
    : ((dest.y + dest.h) < (source.y + source.h)) ?
        (rect_t) {
            .x = source.x,
            .y = dest.y + dest.h,
            .w = source.w,
            .h = source.h - ((dest.y + dest.h) - source.y),
        }
    :
        (rect_t) {
            .x = source.x,
            .y = dest.y,
            .w = source.w,
            .h = dest.h,
        }
    ;
}

/* Make the closest opposite facing horizontal edge touch,
 *  or fill the destination horizontally.
 *        +--+           +----+  |||  +------+       +------+
 *        |  |           |    |  |||  |      |       |      |
 *        +--+  __\      +----+  |||  | +--+ |  __\  +------+
 *   +--+         /   +--+       |||  | |  | |    /  |      |
 *   |  |             |  |       |||  | +--+ |       +------+
 *   +--+             +--+       |||  +------+       +------+
 */
static inline
rect_t DYRECT_PREFIX(reachx)(rect_t dest, rect_t source) {
    return (dest.x > source.x) ?
        (rect_t) {
            .x = source.x,
            .y = source.y,
            .w = dest.x - source.x,
            .h = source.h,
        }
    : ((dest.x + dest.w) < (source.x + source.w)) ?
        (rect_t) {
            .x = dest.x + dest.w,
            .y = source.y,
            .w = source.w - ((dest.x + dest.w)- source.x),
            .h = source.h,
        }
    :
        (rect_t) {
            .x = dest.x,
            .y = source.y,
            .w = dest.w,
            .h = source.h,
        }
    ;
}

#undef x
#undef y
#undef w
#undef h

#endif
// This header is in the Public Domain. If you say this notice is inadequate, I will sue you.
