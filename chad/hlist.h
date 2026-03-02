#ifndef HLIST_H
#define HLIST_H

#include <hvec.h>

#include <stdlib.h>
#include <stdint.h>

#define hlnode_t(type) struct { type d; size_t p, n; }
#define hlist_t(type)  struct { size_t h, t; size_t n; hvec_t(hlnode_t(type)) a; }
#define hliter_t(l) typeof(l.a.a)

#define hl_init(l)   (l.h = l.t = SIZE_MAX, l.n = 0, hv_init(l.a))
#define hl_delete(l) hv_delete(l.a)

#define hl_begin(l)    (l.h  != SIZE_MAX ? &hv_A(l.a, l.h)  : nullptr)
#define hl_end(l)      (l.t  != SIZE_MAX ? &hv_A(l.a, l.t)  : nullptr)
#define hl_next(l, i)  (i->n != SIZE_MAX ? &hv_A(l.a, i->n) : nullptr) /*XXX: maybe warn unsed?*/
#define hl_size(l)     l.n
#define hl_d(i)        i->d

#define hl_add(l, x) (                             \
    hv_addp(l.a),                                  \
    hv_A(l.a, hv_size(l.a)-1).d = x,               \
    (l.t != SIZE_MAX                               \
        ? (                                        \
            hv_A(l.a, l.t).n = hv_size(l.a)-1,     \
            hv_A(l.a, hv_size(l.a)-1).p = l.t,     \
            hv_A(l.a, hv_size(l.a)-1).n = SIZE_MAX \
        ) : (                                      \
            l.h = hv_size(l.a)-1,                  \
            hv_A(l.a, l.h).p = SIZE_MAX,           \
            hv_A(l.a, l.h).n = SIZE_MAX            \
    )),                                            \
    l.t = hv_size(l.a)-1,                          \
    ++l.n                                          \
)

#define hl_remove(l, i) (                                           \
    (i->p != SIZE_MAX) ? (hv_A(l.a, i->p).n = i->n) : (l.h = i->n), \
    (i->n != SIZE_MAX) ? (hv_A(l.a, i->n).p = i->p) : (l.t = i->p), \
    --l.n                                                           \
)

#define hl_foreach(it, l) \
    for (hliter_t(l) _i = hl_begin(l), _flag = (typeof(_flag))0x1l; _flag && _i; _i = hl_next(l, _i), _flag = (typeof(_flag))(uintptr_t)!_flag) \
        for ([[ maybe_unused ]] it = _i; _flag; _flag = (typeof(_flag))(uintptr_t)!_flag)

/* XXX
// Insert before iterator position
void insert(List *list, ListIterator pos, void *data) {
    if (pos == NULL) {
        push(list, data);
        return;
    }

    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->prev = pos->prev;
    node->next = pos;

    if (pos->prev)
        pos->prev->next = node;
    else
        list->head = node;

    pos->prev = node;
    list->size++;
}
*/

#endif
