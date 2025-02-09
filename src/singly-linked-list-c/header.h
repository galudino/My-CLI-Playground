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

typedef struct forward_list_node forward_list_node;

struct forward_list_node {
    int data;
    forward_list_node *next;
};

static inline void forward_list_node_init(forward_list_node *const me,
                                          int data) {
    // If applicable,
    // constructors/initialization functions for `data`
    // should be called here.
    // Move this to the .c file if code becomes more complex.
    me->data = data;
    me->next = (forward_list_node *)0;
}

static inline void forward_list_node_deinit(forward_list_node *const me) {
    // If applicable,
    // destructors/deinitialization functions for `data`
    // should be called here.
    // Move this to the .c file if code becomes more complex.
}

static inline forward_list_node *
forward_list_node_insert_after(forward_list_node *const me,
                               forward_list_node *new_node) {
    new_node->next = me->next;
    me->next = new_node;
    return new_node;
}

static inline forward_list_node *
forward_list_node_erase_after(forward_list_node *pos) {
    forward_list_node *victim = pos->next;
    pos->next = victim->next;
    return victim;
}

typedef struct forward_list forward_list;
typedef forward_list_node *forward_list_iterator;
typedef const forward_list_node *forward_list_const_iterator;

struct forward_list {
    forward_list_node impl;
};

void forward_list_clear(forward_list *const me);

static inline void forward_list_init(forward_list *const me) {
    forward_list_node_init(&me->impl, INT_MIN);
}

static inline void forward_list_deinit(forward_list *const me) {
    forward_list_clear(me);
}

static inline forward_list_iterator
forward_list_before_begin(forward_list *const me) {
    return &me->impl;
}

static inline forward_list_const_iterator
forward_list_cbefore_begin(const forward_list *const me) {
    return &me->impl;
}

static inline forward_list_iterator forward_list_begin(forward_list *const me) {
    return me->impl.next;
}

static inline forward_list_const_iterator
forward_list_cbegin(const forward_list *const me) {
    return me->impl.next;
}

static inline forward_list_iterator forward_list_end(forward_list *const me) {
    return (forward_list_iterator)0;
}

static inline forward_list_const_iterator
forward_list_cend(const forward_list *const me) {
    return (forward_list_const_iterator)0;
}

static inline bool forward_list_empty(forward_list *const me) {
    return forward_list_begin(me) == forward_list_end(me);
}

static inline int *forward_list_front(forward_list *const me) {
    return &forward_list_begin(me)->data;
}

forward_list_iterator forward_list_insert_after(forward_list *const me,
                                                forward_list_const_iterator pos,
                                                int value);
forward_list_iterator forward_list_erase_after(forward_list *const me,
                                               forward_list_const_iterator pos);

static inline void forward_list_push_front(forward_list *const me, int value) {
    forward_list_insert_after(me, forward_list_before_begin(me), value);
}

static inline void forward_list_pop_front(forward_list *const me) {
    forward_list_erase_after(me, forward_list_before_begin(me));
}

void forward_list_foreach(const forward_list *const me,
                          void (*visit)(const forward_list_node *));

#ifdef __APPLE__
void forward_list_foreach_b(const forward_list *const me,
                            void (^visit)(const forward_list_node *));
#endif

int forward_list_puts(const forward_list *const me);

void forward_list_mergesort(forward_list *const me,
                            int (*comparator)(const void *, const void *));

#ifdef __APPLE__
void forward_list_mergesort_b(forward_list *const me,
                              int (^comparator)(const void *, const void *));
#endif

static inline int int_compare_ascending(const void *lhs, const void *rhs) {
    return *(int *)lhs - *(int *)rhs;
}

static inline int int_compare_descending(const void *lhs, const void *rhs) {
    return *(int *)rhs - *(int *)lhs;
}

#endif /* HEADER_H */
