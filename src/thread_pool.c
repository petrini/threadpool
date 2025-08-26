#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "thread_pool.h"

void *thread_function(void *param)
{
    thread_pool_t *pool = (thread_pool_t *)param;
    printf("%d\n", pool->queued);
    return NULL;
}

void thread_pool_init(thread_pool_t *pool)
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

