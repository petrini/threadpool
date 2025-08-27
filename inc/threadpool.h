#ifndef THREADPOOL_H
#define THREADPOOL_H

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
} threadpool_t;
/*
void *thread_function(void *param);

void threadpool_init(threadpool_t *pool);
*/
void threadpool_init(threadpool_t* pool);

void threadpool_destroy(threadpool_t* pool);

void threadpool_add_task(threadpool_t* pool, void (*function)(void*), void* arg);

void example_task(void* arg);

#endif

