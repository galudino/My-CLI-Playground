/*!
    \file       source.c
    \brief      Source file

    \author
    \date
 */

#include "header.h"

#include <stdio.h>
#include <stdlib.h>

static forward_list_node *
forward_list_node_mergesort(forward_list_node *head,
                            int (*comparator)(const void *, const void *));

static forward_list_node *
forward_list_node_mergesort_split(forward_list_node *head);

static forward_list_node *forward_list_node_mergesort_merge(
    forward_list_node *first, forward_list_node *second,
    int (*comparator)(const void *, const void *));

#ifdef __APPLE__
static forward_list_node *
forward_list_node_mergesort_b(forward_list_node *head,
                              int (^comparator)(const void *, const void *));

static forward_list_node *forward_list_node_mergesort_merge_b(
    forward_list_node *first, forward_list_node *second,
    int (^comparator)(const void *, const void *));
#endif

static forward_list_node *
forward_list_node_mergesort(forward_list_node *head,
                            int (*comparator)(const void *, const void *)) {
    // Base case: if the list is empty or has only one node,
    // it's already sorted.
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Split the list into two halves.
    forward_list_node *mid = forward_list_node_mergesort_split(head);

    // Recursively sort each half.
    forward_list_node *left = forward_list_node_mergesort(head, comparator);
    forward_list_node *right = forward_list_node_mergesort(mid, comparator);

    // Merge the two sorted halves.
    return forward_list_node_mergesort_merge(left, right, comparator);
}

static forward_list_node *
forward_list_node_mergesort_split(forward_list_node *head) {
    // If the list is empty or has only one node, it's already sorted.
    if (head == NULL) {
        return head;
    }

    // Use slow and fast pointer technique to find the middle of the list.
    forward_list_node *slow = head;
    forward_list_node *fast = head;

    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Split the list into two halves.
    forward_list_node *mid = slow->next;
    slow->next = NULL;

    return mid;
}

static forward_list_node *forward_list_node_mergesort_merge(
    forward_list_node *first, forward_list_node *second,
    int (*comparator)(const void *, const void *)) {
    // If either list is empty, return the other list
    if (first == NULL) {
        return second;
    }

    if (second == NULL) {
        return first;
    }

    if (comparator(&first->data, &second->data) <= 0) {
        // Recursively merge the rest of the lists and
        // link the result to the current node
        first->next =
            forward_list_node_mergesort_merge(first->next, second, comparator);

        return first;
    }

    // Recursively merge the rest of the lists
    // and link the result to the current node
    second->next =
        forward_list_node_mergesort_merge(first, second->next, comparator);

    return second;
}

#ifdef __APPLE__
static forward_list_node *
forward_list_node_mergesort_b(forward_list_node *head,
                              int (^comparator)(const void *, const void *)) {
    // Base case: if the list is empty or has only one node,
    // it's already sorted.
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Split the list into two halves.
    forward_list_node *mid = forward_list_node_mergesort_split(head);

    // Recursively sort each half.
    forward_list_node *left = forward_list_node_mergesort_b(head, comparator);
    forward_list_node *right = forward_list_node_mergesort_b(mid, comparator);

    // Merge the two sorted halves.
    return forward_list_node_mergesort_merge_b(left, right, comparator);
}

static forward_list_node *forward_list_node_mergesort_merge_b(
    forward_list_node *first, forward_list_node *second,
    int (^comparator)(const void *, const void *)) {
    // If either list is empty, return the other list
    if (first == NULL) {
        return second;
    }

    if (second == NULL) {
        return first;
    }

    if (comparator(&first->data, &second->data) <= 0) {
        // Recursively merge the rest of the lists and
        // link the result to the current node
        first->next = forward_list_node_mergesort_merge_b(first->next, second,
                                                          comparator);

        return first;
    }

    // Recursively merge the rest of the lists
    // and link the result to the current node
    second->next =
        forward_list_node_mergesort_merge_b(first, second->next, comparator);

    return second;
}
#endif

forward_list_node *forward_list_insert_after(forward_list *const me,
                                             forward_list_const_iterator pos,
                                             int value) {
    forward_list_node *new_node = malloc(sizeof *new_node);
    forward_list_node_init(new_node, value);

    return forward_list_node_insert_after((forward_list_node *)pos, new_node);
}

forward_list_node *forward_list_erase_after(forward_list *const me,
                                            forward_list_const_iterator pos) {
    forward_list_node *victim =
        forward_list_node_erase_after((forward_list_node *)pos);
    forward_list_node *next = victim->next;
    forward_list_node_deinit(victim);
    free(victim);
    return next;
}

void forward_list_clear(forward_list *const me) {
    forward_list_node *pos = forward_list_before_begin(me);

    while (pos->next != forward_list_end(me)) {
        forward_list_erase_after(me, pos);
    }
}

void forward_list_foreach(const forward_list *const me,
                          void (*visit)(const forward_list_node *)) {
    const forward_list_node *iterator = forward_list_cbegin(me);
    while (iterator != forward_list_cend(me)) {
        visit(iterator);
        iterator = iterator->next;
    }
}

#ifdef __APPLE__
void forward_list_foreach_b(const forward_list *const me,
                            void (^visit)(const forward_list_node *)) {
    const forward_list_node *iterator = forward_list_cbegin(me);
    while (iterator != forward_list_cend(me)) {
        visit(iterator);
        iterator = iterator->next;
    }
}
#endif

int forward_list_puts(const forward_list *const me) {
    int val = 0;

    val += printf("[");

    const forward_list_node *iterator = forward_list_cbegin(me);
    while (iterator != forward_list_cend(me)) {
        val += printf("%d%c", iterator->data,
                      iterator->next == forward_list_cend(me) ? '\0' : ' ');
        iterator = iterator->next;
    }

    val += printf("]\n");

    return val;
}

void forward_list_mergesort(forward_list *const me,
                            int (*comparator)(const void *, const void *)) {
    me->impl.next = forward_list_node_mergesort(
        (forward_list_iterator)forward_list_cbegin(me), comparator);
}

#ifdef __APPLE__
void forward_list_mergesort_b(forward_list *const me,
                              int (^comparator)(const void *, const void *)) {
    me->impl.next = forward_list_node_mergesort_b(
        (forward_list_iterator)forward_list_cbegin(me), comparator);
}

#endif
