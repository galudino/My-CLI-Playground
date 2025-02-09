/*!
    \file       source.c
    \brief      Source file

    \author
    \date
 */

#include "header.h"

#include <stdio.h>
#include <stdlib.h>

static list_node *list_node_mergesort(list_node *head, list_node *sentinel,
                                      int (*comparator)(const void *,
                                                        const void *));

static list_node *list_node_mergesort_split(list_node *head,
                                            list_node *sentinel);

static list_node *list_node_mergesort_merge(list_node *first, list_node *second,
                                            list_node *sentinel,
                                            int (*comparator)(const void *,
                                                              const void *));

#ifdef __APPLE__
static list_node *list_node_mergesort_b(list_node *head, list_node *sentinel,
                                        int (^comparator)(const void *,
                                                          const void *));

static list_node *
list_node_mergesort_merge_b(list_node *first, list_node *second,
                            list_node *sentinel,
                            int (^comparator)(const void *, const void *));
#endif

static list_node *list_node_mergesort(list_node *head, list_node *sentinel,
                                      int (*comparator)(const void *,
                                                        const void *)) {
    // Base case: if the list is empty or has only one node,
    // it's already sorted.
    if (head == sentinel || head->next == sentinel) {
        return head;
    }

    // Split the list into two halves.
    list_node *mid = list_node_mergesort_split(head, sentinel);

    // Recursively sort each half.
    list_node *left = list_node_mergesort(head, sentinel, comparator);
    list_node *right = list_node_mergesort(mid, sentinel, comparator);

    // Merge the two sorted halves.
    return list_node_mergesort_merge(left, right, sentinel, comparator);
}

static list_node *list_node_mergesort_split(list_node *head,
                                            list_node *sentinel) {
    // If the list is empty or has only one node, it's already sorted.
    if (head == sentinel || head->next == sentinel) {
        return head;
    }

    // Use slow and fast pointer technique to find the middle of the list.
    list_node *slow = head;
    list_node *fast = head;

    while (fast->next != sentinel && fast->next->next != sentinel) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Split the list into two halves.
    list_node *mid = slow->next;
    slow->next = sentinel;
    sentinel->prev = slow;

    return mid;
}

static list_node *list_node_mergesort_merge(list_node *first, list_node *second,
                                            list_node *sentinel,
                                            int (*comparator)(const void *,
                                                              const void *)) {
    // Create a node to build the sorted list.
    list_node list;
    list_node *tail = &list;

    // Merge elements from both lists based on the comparator function.
    while (first != sentinel && second != sentinel) {
        if (comparator(&first->data, &second->data) <= 0) {
            tail->next = first;
            first->prev = tail;
            first = first->next;
        } else {
            tail->next = second;
            second->prev = tail;
            second = second->next;
        }
        tail = tail->next;
    }

    // Append any remaining elements from either list.
    if (first != sentinel) {
        tail->next = first;
        first->prev = tail;
    } else {
        tail->next = second;
        second->prev = tail;
    }

    // Ensure the list remains circular.
    while (tail->next != sentinel) {
        tail = tail->next;
    }
    tail->next = sentinel;
    sentinel->prev = tail;

    // list.next is the "true" head of the list.
    return list.next;
}

#ifdef __APPLE__
static list_node *list_node_mergesort_b(list_node *head, list_node *sentinel,
                                        int (^comparator)(const void *,
                                                          const void *)) {
    // Base case: if the list is empty or has only one node,
    // it's already sorted
    if (head == sentinel || head->next == sentinel) {
        return head;
    }

    // Split the list into two halves.
    list_node *mid = list_node_mergesort_split(head, sentinel);

    // Recursively sort each half.
    list_node *left = list_node_mergesort_b(head, sentinel, comparator);
    list_node *right = list_node_mergesort_b(mid, sentinel, comparator);

    // Merge the two sorted halves.
    return list_node_mergesort_merge_b(left, right, sentinel, comparator);
}

static list_node *
list_node_mergesort_merge_b(list_node *first, list_node *second,
                            list_node *sentinel,
                            int (^comparator)(const void *, const void *)) {
    // Create a node to build the sorted list.
    list_node list;
    list_node *tail = &list;

    // Merge elements from both lists based on the comparator function.
    while (first != sentinel && second != sentinel) {
        if (comparator(&first->data, &second->data) <= 0) {
            tail->next = first;
            first->prev = tail;
            first = first->next;
        } else {
            tail->next = second;
            second->prev = tail;
            second = second->next;
        }
        tail = tail->next;
    }

    // Append any remaining elements from either list.
    if (first != sentinel) {
        tail->next = first;
        first->prev = tail;
    } else {
        tail->next = second;
        second->prev = tail;
    }

    // Ensure the list remains circular.
    while (tail->next != sentinel) {
        tail = tail->next;
    }

    tail->next = sentinel;
    sentinel->prev = tail;

    // list.next is the "true" head of the list.
    return list.next;
}
#endif

list_node *list_insert(list *const me, list_const_iterator pos, int value) {
    list_node *new_node = malloc(sizeof *new_node);
    list_node_init(new_node, value);
    return list_node_insert((list_node *)pos, new_node);
}

list_node *list_erase(list *const me, list_const_iterator pos) {
    list_node *next = pos->next;
    list_node *victim = list_node_erase((list_node *)pos);

    list_node_deinit(victim);
    free(victim);

    return next;
}

void list_clear(list *const me) {
    list_node *pos = list_begin(me);

    while (pos != list_end(me)) {
        pos = list_erase(me, pos);
    }
}

void list_foreach(const list *const me, void (*visit)(const list_node *)) {
    const list_node *iterator = list_cbegin(me);
    while (iterator != list_cend(me)) {
        visit(iterator);
        iterator = iterator->next;
    }
}

#ifdef __APPLE__
void list_foreach_b(const list *const me, void (^visit)(const list_node *)) {
    const list_node *iterator = list_cbegin(me);
    while (iterator != list_cend(me)) {
        visit(iterator);
        iterator = iterator->next;
    }
}
#endif

int list_puts(const list *const me) {
    int val = 0;

    val += printf("[");

    const list_node *iterator = list_cbegin(me);
    while (iterator != list_cend(me)) {
        val += printf("%d%c", iterator->data,
                      iterator->next == list_cend(me) ? '\0' : ' ');
        iterator = iterator->next;
    }

    val += printf("]\n");

    return val;
}

void list_mergesort(list *const me,
                    int (*comparator)(const void *, const void *)) {
    if (list_empty(me)) {
        return;
    }

    me->impl.next =
        list_node_mergesort(me->impl.next, list_end(me), comparator);

    // Re-establish prev pointers and circular links
    list_node *curr = me->impl.next;
    list_node *prev = &me->impl;

    while (curr != list_end(me)) {
        curr->prev = prev;
        prev = curr;
        curr = curr->next;
    }

    prev->next = &me->impl;
    me->impl.prev = prev;
}

#ifdef __APPLE__
void list_mergesort_b(list *const me,
                      int (^comparator)(const void *, const void *)) {
    if (list_empty(me)) {
        return;
    }

    me->impl.next =
        list_node_mergesort_b(me->impl.next, list_end(me), comparator);

    // Re-establish prev pointers and circular links
    list_node *curr = me->impl.next;
    list_node *prev = &me->impl;

    while (curr != list_end(me)) {
        curr->prev = prev;
        prev = curr;
        curr = curr->next;
    }

    prev->next = &me->impl;
    me->impl.prev = prev;
}

#endif
