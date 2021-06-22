/*!
    \file       main.c
    \brief      Client source file

    \author     Gemuele Aludino
    \date
 */

#include "linkedstack.h"
#include "linkedqueue.h"

#include <stdio.h>

void stack_sample();
void queue_sample();

int main(int argc, const char *argv[]) {
    printf("Stack vs. Queue: adding/removing integers [0, 10)\n");

    stack_sample();
    queue_sample();

    return 0;
}

void stack_sample() {
    stack s;
    stack_init(&s);

    for (int i = 0; i < 10; i++) {
        push(&s, i);
    }

    printf("stack: {");
    while (!stack_empty(&s)) {
        printf(" %d ", pop(&s));
    }
    printf("}\n");
}

void queue_sample() {
    queue q;
    queue_init(&q);

    for (int i = 0; i < 10; i++) {
        enqueue(&q, i);
    }

    printf("queue: {");
    while (!queue_empty(&q)) {
        printf(" %d ", dequeue(&q));
    }
    printf("}\n");
}
