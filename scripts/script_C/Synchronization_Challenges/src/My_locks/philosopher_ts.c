#include "../../headers/philosopher.h"


void *create_arg_philosopher(int id, bool rightGreater, pthread_mutex_t *left_baguette, pthread_mutex_t *right_baguette)
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


void philosopher_eating(int id, bool rightGreater, pthread_mutex_t *left_baguette, pthread_mutex_t *right_baguette)
{
    if (rightGreater)
    {
        my_ts_mutex_lock(left_baguette);
        my_ts_mutex_lock(right_baguette);
    }
    else
    {
        my_ts_mutex_lock(right_baguette);
        my_ts_mutex_lock(left_baguette);
    }

    // printf("Philosopher [%d] is eating\n", id);

    my_ts_mutex_unlock(left_baguette);
    my_ts_mutex_unlock(right_baguette);
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
    int *left_baguette = arg_philosopher->left_baguette;
    int *right_baguette = arg_philosopher->right_baguette;

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
    int baguettes[NB_PHILOSOPHERS];

    for (int i = 0; i < NB_PHILOSOPHERS; i++)
    {
        if (my_ts_mutex_init(&baguettes[i], NULL) != 0)
        {
            perror("my_ts_mutex_init()");
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
            for (int j = 0; j < NB_PHILOSOPHERS; j++) my_ts_mutex_destroy(&baguettes[j]);
            perror("create_arg_philosopher()");
            return EXIT_FAILURE;
        }

        if (pthread_create(&philosophers[i], NULL, philosopher_function, args) != 0)
        {
            perror("pthread_create()");
            free(args);
            for (int j = 0; j < NB_PHILOSOPHERS; j++) my_ts_mutex_destroy(&baguettes[j]);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NB_PHILOSOPHERS; i++)
    {
        if (pthread_join(philosophers[i], NULL) != 0)
        {
            perror("pthread_join()");
            for (int j = 0; j < NB_PHILOSOPHERS; j++) my_ts_mutex_destroy(&baguettes[j]);
            return EXIT_FAILURE;
        }
    }

    int error = 0;
    for (int i = 0; i < NB_PHILOSOPHERS; i++)
    {
        if (my_ts_mutex_destroy(&baguettes[i]) != 0) error = 1;
    }

    if (error)
    {
        perror("my_ts_mutex_destroy()");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}