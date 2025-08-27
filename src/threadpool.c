#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "../inc/threadpool.h"

void *thread_function(void *param)
{
    threadpool_t *pool = (threadpool_t *)param;
    printf("%d\n", pool->queued);
    return NULL;
}

void threadpool_init(threadpool_t *pool)
{
    pool->queued = 0;
    pool->queue_front = 0;
    pool->queue_back = 0;
    pool->stop = 0;

    pthread_mutex_init(&(pool->lock), NULL);
    pthread_cond_init(&(pool->notify), NULL);

    for(int i = 0; i < MAX_THREADS; i++)
    {
        pthread_create(&(pool->threads[i]), NULL, thread_function, pool);
    }
}

void threadpool_destroy(threadpool_t* pool)
{
    pthread_mutex_destroy(&(pool->lock));
    pthread_cond_destroy(&(pool->notify));

    for(int i = 0; i < MAX_THREADS; i++)
    {
        pthread_exit(&(pool->threads[i]));
    }
}

void threadpool_add_task(threadpool_t* pool, void (*function)(void*), void* arg)
{
    if(pool->queued == MAX_TASKS)
    {
        fprintf(stderr, "Cannot add task: queue full\n");
        return;
    }

    if(pool->queue_front < MAX_TASKS - 1)
    {
        pool->queue_front++;
    }
    else
    {
        pool->queue_front = 0;
    }
    pool->queued++;
    pool->task_queue[pool->queue_front].fn = function;
    pool->task_queue[pool->queue_front].arg = arg;
}

void example_task(void* arg)
{
    printf("%d\n", *(int *)arg);
}

