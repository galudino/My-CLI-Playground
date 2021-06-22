/*!
    \file       linkedqueue.c
    \brief      Source file

    \author     Gemuele Aludino
    \date
 */

#include "linkedqueue.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>

void queue_init(queue *const self) {
    self->head = NULL;
}

bool enqueue(queue *const self, int val) {
    snode_t *n = snode_new(val);

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

    snode_t *victim = self->head;
    int val = victim->data;

    self->head = self->head->next;
    snode_delete(victim);

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
