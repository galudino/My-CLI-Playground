/*!
    \file       header.h
    \brief      Header file

    \author
    \date
 */

#ifndef HEADER_H
#define HEADER_H

#include <limits.h>
#include <stdbool.h>

typedef struct list_node list_node;

struct list_node {
    int data;
    list_node *next;
    list_node *prev;
};

static inline void list_node_init(list_node *const me, int data) {
    // If applicable,
    // constructors/initialization functions for `data`
    // should be called here.
    // Move this to the .c file if code becomes more complex.
    me->data = data;
    me->next = (list_node *)0;
    me->prev = (list_node *)0;
}

static inline void list_node_deinit(list_node *const me) {
    // If applicable,
    // destructors/deinitialization functions for `data`
    // should be called here.
    // Move this to the .c file if code becomes more complex.
}

static inline list_node *list_node_insert(list_node *const me,
                                          list_node *new_node) {
    new_node->next = me;
    new_node->prev = me->prev;

    me->prev->next = new_node;
    me->prev = new_node;

    return new_node;
}

static inline list_node *list_node_erase(list_node *pos) {
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    return pos;
}

typedef struct list list;
typedef list_node *list_iterator;
typedef const list_node *list_const_iterator;

struct list {
    list_node impl;
};

void list_clear(list *const me);

static inline void list_init(list *const me) {
    list_node_init(&me->impl, INT_MIN);
    me->impl.next = &me->impl;
    me->impl.prev = &me->impl;
}

static inline void list_deinit(list *const me) { list_clear(me); }

static inline list_iterator list_begin(list *const me) { return me->impl.next; }

static inline list_const_iterator list_cbegin(const list *const me) {
    return me->impl.next;
}

static inline list_iterator list_before_end(list *const me) {
    return me->impl.prev;
}

static inline list_const_iterator list_cbefore_end(const list *const me) {
    return me->impl.prev;
}

static inline list_iterator list_end(list *const me) { return &me->impl; }

static inline list_const_iterator list_cend(const list *const me) {
    return &me->impl;
}

static inline bool list_empty(list *const me) {
    return list_begin(me) == list_end(me);
}

static inline const int *list_front(const list *const me) {
    return &list_cbegin(me)->data;
}

static inline const int *list_back(const list *const me) {
    return &list_cbefore_end(me)->data;
}

list_iterator list_insert(list *const me, list_const_iterator pos, int value);
list_iterator list_erase(list *const me, list_const_iterator pos);

static inline void list_push_front(list *const me, int value) {
    list_insert(me, list_begin(me), value);
}

static inline void list_push_back(list *const me, int value) {
    list_insert(me, list_end(me), value);
}

static inline void list_pop_front(list *const me) {
    list_erase(me, list_begin(me));
}

static inline void list_pop_back(list *const me) {
    list_erase(me, list_before_end(me));
}

void list_foreach(const list *const me, void (*visit)(const list_node *));

#ifdef __APPLE__
void list_foreach_b(const list *const me, void (^visit)(const list_node *));
#endif

int list_puts(const list *const me);

void list_mergesort(list *const me,
                    int (*comparator)(const void *, const void *));

#ifdef __APPLE__
void list_mergesort_b(list *const me,
                      int (^comparator)(const void *, const void *));
#endif

static inline int int_compare_ascending(const void *lhs, const void *rhs) {
    return *(int *)lhs - *(int *)rhs;
}

static inline int int_compare_descending(const void *lhs, const void *rhs) {
    return *(int *)rhs - *(int *)lhs;
}

#endif /* HEADER_H */
