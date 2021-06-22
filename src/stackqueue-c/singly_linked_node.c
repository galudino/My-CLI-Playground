/*!
    \file       source.c
    \brief      Source file

    \author     Gemuele Aludino
    \date
 */

#include "singly_linked_node.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>

void snode_init(snode_t *const self, int data) {
    self->data = data;
    self->next = NULL;
}

void snode_deinit(snode_t *const self) {

}

snode_t *snode_new(int data) {
    snode_t *node = malloc(sizeof *node);
    assert(node);
    snode_init(node, data);
    return node;
}

void snode_delete(snode_t *const self) {
    snode_deinit(self);
    free(self);
}
