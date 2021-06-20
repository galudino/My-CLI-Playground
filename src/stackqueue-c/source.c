/*!
    \file       source.c
    \brief      Source file

    \author     Gemuele Aludino
    \date
 */

#include "header.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>

void node_init(node *const self, int data) {
    self->data = data;
    self->next = NULL;
}

void node_deinit(node *const self) {
}

void stack_init(stack *const self) {
    self->node = NULL;
}

void stack_deinit(stack *const self) {
}

bool push(stack *const self, int val) {
    node *n = malloc(sizeof *n);
    assert(n);

    node_init(n, val);

    if (self->node != NULL) {
        n->next = self->node;
    }

    self->node = n;

    return true;
}

int pop(stack *const self) {
    if (stack_empty(self)) {
        return INT_MIN;
    }

    node *victim = self->node;
    int val = victim->data;

    self->node = self->node->next;
    free(victim);

    return val;
}

bool stack_empty(const stack *const self) {
    return self->node == NULL;
}

int top(const stack *const self) {
    return self->node->data;
}

void queue_init(queue *const self) {
    self->head = NULL;
}

bool enqueue(queue *const self, int val) {
    node *n = malloc(sizeof *n);
    assert(n);

    node_init(n, val);

    if (self->tail != NULL) {
        self->tail->next = n;
    }

    self->tail = n;

    if (self->head == NULL) {
        self->head = n;
    }

    return true;
}

int dequeue(queue *const self) {
    if (queue_empty(self)) {
        return INT_MIN;
    }

    node *victim = self->head;
    int val = victim->data;

    self->head = self->head->next;
    free(victim);

    if (self->head == NULL) {
        self->tail = NULL;
    }

    return val;
}

int peek(const queue *const self) {
    return self->head->data;
}

bool queue_empty(const queue *const self) {
    return self->head == NULL && self->tail == NULL;
}
