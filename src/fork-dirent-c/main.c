/*!
    \file       main.c
    \brief      Client source file

    \author     
    \date
 */

#include "header.h"
#include <dirent.h>
#include <unistd.h>

void dir_handler(const char *src, int indent);

/*!
    \brief      Program execution begins here.

    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments 

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    dir_handler("/usr/local/Cellar/gcc/10.2.0_4/include", 0);
    return EXIT_SUCCESS;
}

void dir_handler(const char *src, int indent) {
    pid_t pids[BUFSIZ * 4];
    int pid_size = 0;
    int status = -1;

    DIR *temp = NULL;
    DIR *dir = NULL;
    struct dirent *entry = NULL;

    if (!(dir = opendir(src))) {
        fprintf(stderr, "Directory '%s' does not exist.\n", src);
        return;
    }

    char path[BUFSIZ * 4];
    char ind[BUFSIZ * 4];
    
    memset(ind, ' ', indent);

    while ((entry = readdir(dir))) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 ||
                strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            snprintf(path, sizeof(path), "%s/%s", src, entry->d_name);
            printf("%s%s %s\n", ind, "◊", entry->d_name);
            
            if ((pids[pid_size++] = fork()) == 0) {
                dir_handler(path, indent + 1);
                exit(EXIT_SUCCESS);
            }
        } else {
            snprintf(path, sizeof(path), "%s/%s", src, entry->d_name);
            printf("%s%s %s\n", ind, "•", entry->d_name);
        }
    }
    
    for (int i = 0; i < pid_size; i++) {
        waitpid(pids[i], NULL, 0);
    }
    
    closedir(dir);
}

