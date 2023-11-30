#include "../headers/philosopher.h"

/*
gcc -DTTS_MUTEX scripts/script_C/active_locks_implementation/src/mutex_tts.c script
s/script_C/mutex/mutex.c scripts/script_C/Synchronization_Challenges/src/philosopher.c -o PHILOSOPHERRRR.out
*/
void *create_arg_philosopher(int id, bool rightGreater, void *left_baguette, void *right_baguette)
{
    args_philosopher_t *args_philosopher = malloc(sizeof(args_philosopher_t));
    if (args_philosopher == NULL)
    {
        perror("malloc()");
        return NULL;
    }
    args_philosopher->id = id;
    args_philosopher->rightGreater = rightGreater;
    args_philosopher->left_baguette = left_baguette;
    args_philosopher->right_baguette = right_baguette;
    return args_philosopher;
}


void philosopher_eating(int id, bool rightGreater, void *left_baguette, void *right_baguette)
{
    if (rightGreater)
    {
        lock_mutex(left_baguette);
        lock_mutex(right_baguette);
    }
    else
    {
        lock_mutex(right_baguette);
        lock_mutex(left_baguette);
    }

    // printf("Philosopher [%d] is eating\n", id);

    unlock_mutex(left_baguette);
    unlock_mutex(right_baguette);
}


void philosopher_thinking(int id)
{
    // printf("Philosopher [%d] is thinking.\n", id);
}


void *philosopher_function(void* arg)
{
    args_philosopher_t *arg_philosopher = (args_philosopher_t *) arg;

    int id = arg_philosopher->id;
    bool rightGreater = arg_philosopher->rightGreater;
    void *left_baguette = arg_philosopher->left_baguette;
    void *right_baguette = arg_philosopher->right_baguette;

    for (int i = 0; i < 10000000; i++)
    {
        // Philosopher thinks
        philosopher_thinking(id);

        // Philosopher eats
        philosopher_eating(id, rightGreater, left_baguette, right_baguette);
    }

    free(arg_philosopher);
    // printf("Philosopher [%d] has finished his job.\n", id);
    return NULL;
}


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        perror("argc != 2");
        return EXIT_FAILURE;
    }

    const int NB_PHILOSOPHERS = atoi(argv[1]);

    if (NB_PHILOSOPHERS <= 1)
    {
        perror("NB_PHILOSOPHERS <= 1");
        return EXIT_FAILURE;
    }

    pthread_t philosophers[NB_PHILOSOPHERS];

    #ifdef POSIX
    pthread_mutex_t baguettes[NB_PHILOSOPHERS];
    #else
    my_mutex_t *baguettes[NB_PHILOSOPHERS];
    #endif

    for (int i = 0; i < NB_PHILOSOPHERS; i++)
    {
        if (init_mutex(&baguettes[i]) != 0)
        {
            perror("init_mutex()");
            return EXIT_FAILURE;
        }
    }

    bool rightGreater;
    int i = 0;
    for (i = 0; i < NB_PHILOSOPHERS; i++)
    {
        rightGreater = ((i + 1) % NB_PHILOSOPHERS > i) ? true : false;
        void *args = create_arg_philosopher(i, rightGreater, &baguettes[i], &baguettes[(i + 1) % NB_PHILOSOPHERS]);
        if (args == NULL)
        {
            for (int j = 0; j < NB_PHILOSOPHERS; j++) destroy_mutex(&baguettes[j]);
            return EXIT_FAILURE;
        }

        if (pthread_create(&philosophers[i], NULL, philosopher_function, args) != 0)
        {
            perror("pthread_create()");
            free(args);
            for (int j = 0; j < NB_PHILOSOPHERS; j++) destroy_mutex(&baguettes[j]);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NB_PHILOSOPHERS; i++)
    {
        if (pthread_join(philosophers[i], NULL) != 0)
        {
            perror("pthread_join()");
            for (int j = 0; j < NB_PHILOSOPHERS; j++) destroy_mutex(&baguettes[j]);
            return EXIT_FAILURE;
        }
    }

    printf("WOW\n");

    int error = 0;
    for (int i = 0; i < NB_PHILOSOPHERS; i++)
    {
        if (destroy_mutex(&baguettes[i]) != 0) error = 1;
    }

    if (error)
    {
        perror("destroy_mutex()");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}