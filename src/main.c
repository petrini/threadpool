#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "threadpool.h"

void placeholder_task(void *arg)
{
    int* num = (int*)arg;
    printf("Processing task %d\n", *num);
    sleep(1);
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage %s <number of tasks>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int task_amount = atoi(argv[1]);
    if(task_amount < 1)
    {
        printf("Invalid number of tasks <%d>\n", task_amount);
        exit(EXIT_FAILURE);
    }

    threadpool_t pool;
    threadpool_init(&pool);

    int* task_num = (int*)malloc(sizeof(int) * task_amount);
    for(int i = 0; i < task_amount; i++)
    {
       task_num[i] = i + 1;
       threadpool_add_task(&pool, placeholder_task, &task_num[i]);
    }

    sleep(15);

    free((void*)task_num);
    threadpool_destroy(&pool);

    return 0;
}

