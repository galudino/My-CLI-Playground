/*!
    \file       main.c
    \brief      Client source file

    \author
    \date
 */

#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void list_test();
// void inline_node_test();

int rand_range(int min, int max);

/*!
    \brief      Program execution begins here.

    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    srand((unsigned)time(NULL));
    list_test();

    return EXIT_SUCCESS;
}

void list_test() {
    list list;
    list_init(&list);

    list_node *iterator = list_begin(&list);

    for (int i = 1; i <= 10; i++) {
        iterator = list_insert(&list, iterator, rand_range(50, 100));
    }

    printf("List of 10 random values from 50 to 100\n");
    list_puts(&list);
    puts("");

    printf("Popping %d\n", *list_back(&list));
    list_pop_back(&list);

    list_puts(&list);
    puts("");

    printf("Pushing %d\n", 5280);
    list_push_back(&list, 5280);

    list_puts(&list);
    puts("");

#ifdef __APPLE__
    printf("Applying mergesort to list\n");
    list_mergesort_b(&list, ^(const void *lhs, const void *rhs) {
      return *(int *)lhs - *(int *)rhs;
    });
#else
    printf("Applying mergesort to list\n");
    list_mergesort(&list, int_compare);
#endif

    list_puts(&list);
    puts("");

    printf("Clearing list\n");
    list_clear(&list);

    list_puts(&list);
    puts("");

    printf("Is list empty? %s\n", list_empty(&list) ? "yes" : "no");
}

int rand_range(int min, int max) { return rand() % (max + 1 - min) + min; }

/*
void inline_node_test() {
    node list;
    node *const list_before_begin = &list;

    list.data = INT_MIN;
    list.next = NULL;

    node *iterator = list_before_begin;

    for (int i = 1; i <= 10; i++) {
        node *new_node = malloc(sizeof *new_node);
        node_init(new_node, i * 10);
        iterator = node_insert_after(iterator, new_node);
    }

    iterator = list.next;

    printf("[");
    while (iterator != NULL) {
        printf("%d%c", iterator->data, iterator->next == NULL ? '\0' : ' ');
        iterator = iterator->next;
    }
    printf("]\n");

    iterator = &list;

    while (iterator->next != NULL) {
        node *victim = node_erase_after(iterator);
        node_deinit(victim);
        free(victim);
    }

    iterator = list.next;

    printf("[");
    while (iterator != NULL) {
        printf("%d%c", iterator->data, iterator->next == NULL ? '\0' : ' ');
        iterator = iterator->next;
    }
    printf("]\n");
}
*/
