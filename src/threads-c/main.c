/*!
    \file       main.c
    \brief      Client source file

    \author     
    \date
 */

#include "header.h"


/*!
    \brief      Program execution begins here.

    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments 

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    pthread_t v_thread[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];

    shared_data = 0.0;
    pthread_mutex_init(&lock_shared_data, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].m_tid = i;
        thread_data[i].m_data = i + 1;

        int result = -1;
        if ((result = pthread_create(v_thread + i, NULL, thread_function, thread_data + i))) {
            fprintf(stderr, "error: pthread_create, result: %d\n", result);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(v_thread[i], NULL);
    }
    
    printf("Final sum: %f\n", shared_data);

    return EXIT_SUCCESS;
}

