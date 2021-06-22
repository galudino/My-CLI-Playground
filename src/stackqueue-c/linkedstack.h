/*!
    \file       linkedstack.h
    \brief      Header file

    \author     Gemuele Aludino
    \date
 */

#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include "singly_linked_node.h"
#include <stdbool.h>

typedef struct stack stack;

struct stack {
    snode_t *node;
};

void stack_init(stack *const self);
void stack_deinit(stack *const self);

bool push(stack *const self, int val);
int pop(stack *const self);

bool stack_empty(const stack *const self);
int top(const stack *const self);

#endif /* LINKEDSTACK_H */
