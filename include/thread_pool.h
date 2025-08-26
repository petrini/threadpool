#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 8
#define MAX_TASKS 128

typedef struct
{
    void (* fn) (void *task);
    void *arg;
} task_t;

typedef struct
{
    pthread_mutex_t lock;
    pthread_cond_t notify;
    pthread_t threads[MAX_THREADS];
    task_t task_queue[MAX_TASKS];
    int queued;
    int queue_front;
    int queue_back;
    int stop;
} thread_pool_t;

void *thread_function(void *param);

void thread_pool_init(thread_pool_t *pool);

#endif

