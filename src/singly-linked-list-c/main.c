/*!
    \file       main.c
    \brief      Client source file

    \author
    \date
 */

#include "header.h"

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
    forward_list list;
    forward_list_init(&list);

    node *iterator = forward_list_before_begin(&list);

    for (int i = 1; i <= 10; i++) {
        iterator =
            forward_list_insert_after(&list, iterator, rand_range(50, 100));
    }

    printf("List of 10 random values from 50 to 100\n");
    forward_list_puts(&list);
    puts("");

    printf("Popping %d\n", *forward_list_front(&list));
    forward_list_pop_front(&list);

    forward_list_puts(&list);
    puts("");

    printf("Pushing %d\n", 5280);
    forward_list_push_front(&list, 5280);

    forward_list_puts(&list);
    puts("");

    printf("Applying mergesort to list\n");
    forward_list_mergesort(&list);

    forward_list_puts(&list);
    puts("");

    printf("Clearing list\n");
    forward_list_clear(&list);

    forward_list_puts(&list);
    puts("");
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
