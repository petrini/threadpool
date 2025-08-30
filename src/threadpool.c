#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "../inc/threadpool.h"

void* thread_function(void* arg)
{
    threadpool_t* pool = (threadpool_t*)arg;

    while(true)
    {
        pthread_mutex_lock(&(pool->lock));

        while(pool->queue_size == 0 && !pool->stop)
        {
            pthread_cond_wait(&(pool->notify), &(pool->lock));
        }

        if(pool->stop)
        {
            pthread_mutex_unlock(&(pool->lock));
            pthread_exit(NULL);
        }

        task_t task = pool->task_queue[pool->queue_front];
        pool->queue_front = (pool->queue_front + 1) % QUEUE_SIZE;
        pool->queue_size--;

        pthread_mutex_unlock(&(pool->lock));

        (*(task.function))(task.arg);
    }
}

void threadpool_init(threadpool_t *pool)
{
    pool->queue_size = 0;
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
    pthread_mutex_lock(&(pool->lock));
    pool->stop = true;
    pthread_cond_broadcast(&(pool->notify));
    pthread_mutex_unlock(&(pool->lock));


    for(int i = 0; i < MAX_THREADS; i++)
    {
        pthread_join(pool->threads[i], NULL);
    }

    pthread_mutex_destroy(&(pool->lock));
    pthread_cond_destroy(&(pool->notify));
}

void threadpool_add_task(threadpool_t* pool, void (*function)(void*), void* arg)
{
    pthread_mutex_lock(&(pool->lock));

    if(pool->queue_size == QUEUE_SIZE)
    {
        fprintf(stderr, "Cannot add task: queue full\n");
    }
    else
    {
        pool->task_queue[pool->queue_back].function = function;
        pool->task_queue[pool->queue_back].arg = arg;
        pool->queue_back = (pool->queue_back + 1) % QUEUE_SIZE;
        pool->queue_size++;
        pthread_cond_signal(&(pool->notify));
    }

    pthread_mutex_unlock(&(pool->lock));
}

