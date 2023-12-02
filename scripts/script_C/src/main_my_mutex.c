#include "../headers/main_my_mutex.h"

void process(void)
{
    for (int i = 0; i < 10000; i++);
}

void *thread_function(void *arg)
{
    for (int i = 0; i < NBER_ITER; i++)
    {
        lock_mutex(my_mutex);
        process();
        unlock_mutex(my_mutex);
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

    init_mutex(&my_mutex);

    for (int i = 0; i < NB_THREADS; i++) pthread_create(&threads[i], NULL, thread_function, NULL);
    for (int i = 0; i < NB_THREADS; i++) pthread_join(threads[i], NULL);

    destroy_mutex(my_mutex);

    return EXIT_SUCCESS;
}