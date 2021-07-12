/*!
    \file       source.c
    \brief      Source file

    \author     
    \date
 */

#include "header.h"

double shared_data;
pthread_mutex_t lock_shared_data = PTHREAD_MUTEX_INITIALIZER;

void *thread_function(void *arg) {
    thread_data_t *tdata = (thread_data_t *)(arg);
    printf("Hello from thread_function, thread id: %d\n", tdata->m_tid);
    
    pthread_mutex_lock(&lock_shared_data);
    shared_data += tdata->m_data;
    pthread_mutex_unlock(&lock_shared_data);

    pthread_exit(NULL);
}

