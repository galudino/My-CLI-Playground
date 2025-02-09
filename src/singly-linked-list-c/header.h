/*!
    \file       header.h
    \brief      Header file

    \author
    \date
 */

#ifndef HEADER_H
#define HEADER_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct node node;
struct node {
    int data;
    node *next;
};

typedef struct forward_list forward_list;
typedef node *forward_list_iterator;
typedef const node *forward_list_const_iterator;

struct forward_list {
    node impl;
};

void forward_list_init(forward_list *const me);
void forward_list_deinit(forward_list *const me);

forward_list_iterator forward_list_before_begin(forward_list *const me);
forward_list_const_iterator
forward_list_cbefore_begin(const forward_list *const me);

forward_list_iterator forward_list_begin(forward_list *const me);
forward_list_const_iterator forward_list_cbegin(const forward_list *const me);

forward_list_iterator forward_list_end(forward_list *const me);
forward_list_const_iterator forward_list_cend(const forward_list *const me);

int *forward_list_front(forward_list *const me);

forward_list_iterator forward_list_insert_after(forward_list *const me,
                                                forward_list_const_iterator pos,
                                                int value);
forward_list_iterator forward_list_erase_after(forward_list *const me,
                                               forward_list_const_iterator pos);

void forward_list_push_front(forward_list *const me, int value);
void forward_list_pop_front(forward_list *const me);

void forward_list_clear(forward_list *const me);

void forward_list_foreach(const forward_list *const me,
                          void (*visit)(const node *));

#ifdef __APPLE__
void forward_list_foreach_b(const forward_list *const me,
                            void (^visit)(const node *));
#endif

int forward_list_puts(const forward_list *const me);

void forward_list_mergesort(forward_list *const me);

#endif /* HEADER_H */
