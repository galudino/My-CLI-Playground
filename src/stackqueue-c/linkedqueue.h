/*!
    \file       linkedqueue.h
    \brief      Header file

    \author     Gemuele Aludino
    \date
 */

#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include "singly_linked_node.h"
#include <stdbool.h>

typedef struct queue queue;

struct queue {
    snode_t *head;
    snode_t *tail;
};

void queue_init(queue *const self);
void queue_deinit(queue *const self);

bool enqueue(queue *const self, int val);
int dequeue(queue *const self);

bool queue_empty(const queue *const self);
int peek(const queue *const self);

#endif /* HEADER_H */
