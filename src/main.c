#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/*
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_function(void *arg)
{
    int *local_counter = (int *)arg;
    pthread_mutex_lock(&mutex);
    (*local_counter)++;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void startup_function()
{
    pthread_t thread_id[10] = {0};
    int counter = 0;
    for(int i = 0; i < 10; i++)
    {
        if(pthread_create(&thread_id[i], NULL, thread_function, (void *)&counter) != 0)
        {
            fprintf(stderr, "Thread creation failed\n");
            exit(EXIT_FAILURE);
        }
        printf("Thread %d started\n", i);
    }

    for(int i = 0; i < 10; i++)
    {
        if(pthread_join(thread_id[i], NULL) != 0)
        {
            fprintf(stderr, "Thread joinage failed\n");
            exit(EXIT_FAILURE);
        }
        printf("Thread %d joined\n", i);
    }

    pthread_mutex_destroy(&mutex);

    printf("Counter: %d\n", counter);
}
*/
int main(int argc, char *argv[])
{
//    startup_function();
    printf("%d %s\n", argc, argv[0]);

    return 0;
}

