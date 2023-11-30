#include "../headers/main_mutex.h"

#define TS_MUTEX

#ifdef TS_MUTEX
    #include "../headers/test_and_set.h"
    #define init_mutex my_mutex_ts_init
    #define destroy_mutex my_mutex_ts_destroy
    #define lock_mutex my_mutex_ts_lock
    #define unlock_mutex my_mutex_ts_unlock
#else
    #include "../headers/test_and_test_and_set.h"
    #define init_mutex my_mutex_tts_init
    #define destroy_mutex my_mutex_tts_destroy
    #define lock_mutex my_mutex_tts_lock
    #define unlock_mutex my_mutex_tts_unlock
#endif


void init_mutex();
void destroy_mutex();
void lock_mutex();
void unlock_mutex();

int NBER_ITER;

void process(void)
{
    for (int i = 0; i < 10000; i++);
}

void *thread_function(void *arg)
{
    for (int i = 0; i < NBER_ITER; i++)
    {
        lock_mutex();
        process();
        unlock_mutex();
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

    if (init_mutex() != 0)
    {
        perror("my_tts_init()");
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

    if (destroy_mutex() != 0)
    {
        perror("my_tts_destroy()");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}