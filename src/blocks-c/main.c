/*!
    \file       main.c
    \brief      Client source file - block syntax

    \author     Gemuele Aludino
    \date       24 June 2021
 */

#include "header.h"

void print_array(void *base, size_t count, size_t width,
                 void (^print_b)(void *));

void sample_intarray();
void sample_charptrarray();

/*!
    \brief      Program execution begins here.

    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    puts("Array of int:");
    sample_intarray();

    puts("\nArray of (char *):");
    sample_charptrarray();

    return EXIT_SUCCESS;
}

void sample_intarray() {
    int intarr[] = {5, 2, 1, 3, 0, 4, 7, 6};

    const size_t intarr_size = sizeof(intarr) / sizeof *intarr;

    print_array(intarr, intarr_size, sizeof *intarr, ^(void *arg) {
      printf(" %d ", *(int *)(arg));
    });

    qsort_b(intarr, intarr_size, sizeof *intarr,
            ^(const void *c0, const void *c1) {
              return *(int *)(c0) - *(int *)(c1);
            });

    print_array(intarr, intarr_size, sizeof *intarr, ^(void *arg) {
      printf(" %d ", *(int *)(arg));
    });
}

void sample_charptrarray() {
    const char *charptrarr[] = {"Beta", "Echo",  "Charlie", "Delta", "Hotel",
                                "Kilo", "Alpha", "Foxtrot", "Golf"};

    const size_t charptrarr_size = sizeof(charptrarr) / sizeof *charptrarr;

    print_array(charptrarr, charptrarr_size, sizeof *charptrarr, ^(void *arg) {
      printf(" %s ", *(char **)(arg));
    });

    qsort_b(charptrarr, charptrarr_size, sizeof *charptrarr,
            ^(const void *c0, const void *c1) {
              return strcmp(*(char **)(c0), *(char **)(c1));
            });

    print_array(charptrarr, charptrarr_size, sizeof *charptrarr, ^(void *arg) {
      printf(" %s ", *(char **)(arg));
    });
}

void print_array(void *base, size_t count, size_t width,
                 void (^print_b)(void *)) {
    printf("count: %lu {", count);
    for (int i = 0; i < count; i++) {
        void *element = (char *)(base) + (width * i);
        print_b(element);
    }
    printf("}\n");
}
