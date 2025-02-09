/*!
    \file       source.c
    \brief      Source file

    \author
    \date
 */

#include "header.h"

static void node_init(node *const me, int data);
static void node_deinit(node *const me);
static node *node_insert_after(node *const me, node *new_node);
static node *node_erase_after(node *pos);

static node *node_mergesort(node *head);
static node *node_mergesort_split(node *head);
static node *node_mergesort_merge(node *first, node *second);

static void node_init(node *const me, int data) {
    // If applicable,
    // constructors/initialization functions for `data`
    // should be called here.
    me->data = data;
    me->next = NULL;
}

static void node_deinit(node *const me) {
    // If applicable,
    // destructors/deinitialization functions for `data`
    // should be called here.
}

static node *node_insert_after(node *const me, node *new_node) {
    new_node->next = me->next;
    me->next = new_node;
    return new_node;
}

static node *node_erase_after(node *pos) {
    node *victim = pos->next;
    pos->next = victim->next;
    return victim;
}

static node *node_mergesort(node *head) {
    // Base case: if the list is empty or has only one node,
    // it's already sorted
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Split the list into two halves
    node *second = node_mergesort_split(head);

    // Recursively sort each half
    head = node_mergesort(head);
    second = node_mergesort(second);

    // Merge the two sorted halves
    return node_mergesort_merge(head, second);
}

static node *node_mergesort_split(node *head) {
    node *fast = head;
    node *slow = head;

    // Move fast pointer two steps and slow pointer
    // one step until fast reaches the end
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        if (fast != NULL) {
            slow = slow->next;
        }
    }

    // Split the list into two halves
    node *temp = slow->next;
    slow->next = NULL;

    return temp;
}

static node *node_mergesort_merge(node *first, node *second) {
    // If either list is empty, return the other list
    if (first == NULL) {
        return second;
    }

    if (second == NULL) {
        return first;
    }

    // Pick the smaller value between first and second nodes
    if (first->data < second->data) {
        // Recursively merge the rest of the lists and
        // link the result to the current node
        first->next = node_mergesort_merge(first->next, second);

        // For doubly-linked lists
        // first->next->prev = first;
        // first->prev = NULL;
        
        return first;
    }

    // Recursively merge the rest of the lists
    // and link the result to the current node
    second->next = node_mergesort_merge(first, second->next);
    
    // For doubly-linked lists
    // second->next->prev = second;
    // second->prev = NULL;
    return second;
}

void forward_list_init(forward_list *const me) {
    node_init(&me->impl, INT_MIN);
}

void forward_list_deinit(forward_list *const me) { forward_list_clear(me); }

node *forward_list_before_begin(forward_list *const me) { return &me->impl; }

const node *forward_list_cbefore_begin(const forward_list *const me) {
    return &me->impl;
}

node *forward_list_begin(forward_list *const me) { return me->impl.next; }

const node *forward_list_cbegin(const forward_list *const me) {
    return me->impl.next;
}

node *forward_list_end(forward_list *const me) { return NULL; }

const node *forward_list_cend(const forward_list *const me) { return NULL; }

int *forward_list_front(forward_list *const me) {
    return &forward_list_begin(me)->data;
}

node *forward_list_insert_after(forward_list *const me,
                                forward_list_const_iterator pos, int value) {
    node *new_node = malloc(sizeof *new_node);
    node_init(new_node, value);

    return node_insert_after((node *)pos, new_node);
}

node *forward_list_erase_after(forward_list *const me,
                               forward_list_const_iterator pos) {
    node *victim = node_erase_after((node *)pos);
    node *next = victim->next;
    node_deinit(victim);
    free(victim);
    return next;
}

void forward_list_push_front(forward_list *const me, int value) {
    forward_list_insert_after(me, forward_list_before_begin(me), value);
}

void forward_list_pop_front(forward_list *const me) {
    forward_list_erase_after(me, forward_list_before_begin(me));
}

void forward_list_clear(forward_list *const me) {
    node *pos = forward_list_before_begin(me);

    while (pos->next != forward_list_end(me)) {
        forward_list_erase_after(me, pos);
    }
}

void forward_list_foreach(const forward_list *const me,
                          void (*visit)(const node *)) {
    const node *iterator = forward_list_cbegin(me);
    while (iterator != forward_list_cend(me)) {
        visit(iterator);
        iterator = iterator->next;
    }
}

#ifdef __APPLE__
void forward_list_foreach_b(const forward_list *const me,
                            void (^visit)(const node *)) {
    const node *iterator = forward_list_cbegin(me);
    while (iterator != forward_list_cend(me)) {
        visit(iterator);
        iterator = iterator->next;
    }
}
#endif

int forward_list_puts(const forward_list *const me) {
    int val = 0;

    val += printf("[");

    const node *iterator = forward_list_cbegin(me);
    while (iterator != forward_list_cend(me)) {
        val += printf("%d%c", iterator->data, iterator->next == NULL ? 0 : ' ');
        iterator = iterator->next;
    }

    val += printf("]\n");

    return val;
}

void forward_list_mergesort(forward_list *const me) {
    me->impl.next =
        node_mergesort((forward_list_iterator)forward_list_cbegin(me));
}
