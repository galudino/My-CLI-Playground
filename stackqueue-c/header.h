/*!
    \file       header.h
    \brief      Header file

    \author     Gemuele Aludino
    \date
 */

#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>

typedef struct node node;

struct node {
    node *next;
    int data;
};

typedef struct node node;

void node_init(node *const self, int data);
void node_deinit(node *const self);

typedef struct stack stack;

struct stack {
    node *node;
};

void stack_init(stack *const self);
void stack_deinit(stack *const self);

bool push(stack *const self, int val);
int pop(stack *const self);

bool stack_empty(const stack *const self);
int top(const stack *const self);

typedef struct queue queue;

struct queue {
    node *head;
    node *tail;
};

void queue_init(queue *const self);
void queue_deinit(queue *const self);

bool enqueue(queue *const self, int val);
int dequeue(queue *const self);

bool queue_empty(const queue *const self);
int peek(const queue *const self);

#endif /* HEADER_H */
