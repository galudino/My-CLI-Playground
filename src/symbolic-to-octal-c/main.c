/*!
    \file       main.c
    \brief      Client source file

    \author     
    \date
 */

#include "header.h"

#define MAX_PERM_STRING_SIZE    10
#define MAX_PERM_TYPE_SIZE      3
#define MAX_RESULT_STRING_SIZE  4
#define MAX_PERM_VALUE          7

#define PARAMETER_STRING        "-rwxr-x-w-"

int symbolic_to_octal(const char *perm_string);

/*!
    \brief      Program execution begins here.
    \return     0 on success, non-zero on failure
 */
int main(void) {
    int result = symbolic_to_octal(PARAMETER_STRING);
    
    switch (result) {
    case INT_MAX:
        fprintf(stderr, "Input string '%s' was of invalid size. Must be size %lu.", 
                PARAMETER_STRING, (size_t)(MAX_PERM_STRING_SIZE));
        break;
    case INT_MIN:
        break;
    default:
        printf("%d\n", result);
        break;
    }

    return EXIT_SUCCESS;
}

int symbolic_to_octal(const char *perm_string) {
    size_t string_size = strlen(perm_string);

    if (string_size != MAX_PERM_STRING_SIZE) { return INT_MAX; }

    int user_perm = 0;
    int curr_perm_group = 0;
    
    int vals[] = { 0, 0, 0 };

    // Start at index 1, not at 0.
    // perm_string[0] is 
    //  '-' if it is a file
    //  'd' if it is a directory
    for (size_t pos = 1; pos < string_size; pos++) {
        // perm_string[1] though perm_string[string_size - 1]
        // is the permission type.
        switch (perm_string[pos]) {
        case 'r': user_perm += 4; break;
        case 'w': user_perm += 2; break;
        case 'x': user_perm += 1; break;
        default: break;
        }
        
        if (user_perm > MAX_PERM_VALUE) {
            fprintf(stderr, 
                    "Invalid string, see index %lu: '%c' in %s\nSum '%d' > 7.\n",
                    pos, perm_string[pos], perm_string, user_perm);
            return INT_MIN;
        }

        if (pos % MAX_PERM_TYPE_SIZE == 0) {
            vals[curr_perm_group++] = user_perm;
            user_perm = 0;
        }
    }

    char result_buf[MAX_RESULT_STRING_SIZE];
    sprintf(result_buf, "%d%d%d", vals[0], vals[1], vals[2]);

    return strtol(result_buf, NULL, MAX_PERM_STRING_SIZE);
}

