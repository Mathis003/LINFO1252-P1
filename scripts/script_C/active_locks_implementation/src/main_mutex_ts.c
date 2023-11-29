#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mutex_ts.c"

int NBER_ITER;

int counter = 0;
void process(void)
{
    // printf("process\n");
    counter++;
    for (int i = 0; i < 10000; i++);
}

void *thread_function(void *arg)
{
    for (int i = 0; i < NBER_ITER; i++)
    {
        my_ts_mutex_lock();
        process();
        my_ts_mutex_unlock();
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        perror("argc != 2");
        return EXIT_FAILURE;
    }

    const int NB_THREADS = atoi(argv[1]);
    pthread_t threads[NB_THREADS];

    if (NB_THREADS <= 0)
    {
        perror("NB_THREADS <= 0");
        return EXIT_FAILURE;
    }

    NBER_ITER = 6400 / NB_THREADS;

    if (my_ts_mutex_init() != 0)
    {
        perror("my_ts_init()");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < NB_THREADS; i++)
    {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0)
        {
            perror("pthread_create()");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NB_THREADS; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            perror("pthread_join()");
            return EXIT_FAILURE;
        }
    }

    if (my_ts_mutex_destroy() != 0)
    {
        perror("my_ts_destroy()");
        return EXIT_FAILURE;
    }

    printf("counter = %d\n", counter);

    

    return EXIT_SUCCESS;
}