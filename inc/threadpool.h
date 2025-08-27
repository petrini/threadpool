#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <stdbool.h>
#include <pthread.h>

#define MAX_THREADS 8
#define MAX_TASKS 128

typedef struct
{
    void (* function) (void *task);
    void *arg;
} task_t;

typedef struct
{
    pthread_mutex_t lock;
    pthread_cond_t notify;
    pthread_t threads[MAX_THREADS];
    task_t task_queue[MAX_TASKS];
    int queue_size;
    int queue_front;
    int queue_back;
    bool stop;
} threadpool_t;

void *thread_function(void *param);

void threadpool_init(threadpool_t* pool);

void threadpool_destroy(threadpool_t* pool);

void threadpool_add_task(threadpool_t* pool, void (*function)(void*), void* arg);

#endif

