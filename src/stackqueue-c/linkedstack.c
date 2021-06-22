/*!
    \file       linkedstack.c
    \brief      Source file

    \author     Gemuele Aludino
    \date
 */

#include "linkedstack.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>

void stack_init(stack *const self) {
    self->node = NULL;
}

void stack_deinit(stack *const self) {
}

bool push(stack *const self, int val) {
    snode_t *n = snode_new(val);

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

    snode_t *victim = self->node;
    int val = victim->data;

    self->node = self->node->next;
    snode_delete(victim);

    return val;
}

bool stack_empty(const stack *const self) {
    return self->node == NULL;
}

int top(const stack *const self) {
    return self->node->data;
}
