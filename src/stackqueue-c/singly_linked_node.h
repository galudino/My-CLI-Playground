/*!
    \file       singly_linked_node.h
    \brief      Header file

    \author     Gemuele Aludino
    \date
 */

#ifndef SINGLY_LINKED_NODE_H
#define SINGLY_LINKED_NODE_H

typedef struct singly_linked_node snode_t;

struct singly_linked_node {
    int data;
    snode_t *next;
};

void snode_init(snode_t *const self, int data);
void snode_deinit(snode_t *const self);

snode_t *snode_new(int data);
void snode_delete(snode_t *const self);

#endif /* SINGLY_LINKED_NODE_H */
