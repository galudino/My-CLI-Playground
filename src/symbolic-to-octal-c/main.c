/*!
    \file       main.c
    \brief      Client source file

    \author     
    \date
 */

#include "header.h"

int symbolic_to_octal(const char *perm_string) {
    size_t len = strlen(perm_string);

    if (len != 10) { return 999; }

    int vals[3];
    int val = 0;
    int k = 0;

    for (int i = 1; i < len; i++) {
        switch (perm_string[i]) {
        case 'r': val += 4; break;
        case 'w': val += 2; break;
        case 'x': val += 1; break;
        default: break;
        }

        if (i % 3 == 0) {
            vals[k++] = val;
            val = 0;
        }
    }

    char buf[5];
    sprintf(buf, "%d%d%d", vals[0], vals[1], vals[2]);
    return strtol(buf, NULL, 10);
}

/*!
    \brief      Program execution begins here.

    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments 

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    printf("%d\n", symbolic_to_octal("-rwxr-x-w-")); 
    return EXIT_SUCCESS;
}

