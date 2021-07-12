/*!
    \file       header.h
    \brief      Header file

    \author     
    \date
 */

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>

#define NUM_THREADS 16

typedef struct thread_data thread_data_t;

struct thread_data {
    int m_tid;
    double m_data;
};

extern double shared_data;
extern pthread_mutex_t lock_shared_data;

void *thread_function(void *arg);

#endif /* HEADER_H */

