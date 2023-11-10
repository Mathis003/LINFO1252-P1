#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>


typedef struct args_philosopher
{
    int id;
    bool rightGreater;
    pthread_mutex_t *left_baguette;
    pthread_mutex_t *right_baguette;
} args_philosopher_t;


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
        pthread_mutex_lock(left_baguette);
        pthread_mutex_lock(right_baguette);
    }
    else
    {
        pthread_mutex_lock(right_baguette);
        pthread_mutex_lock(left_baguette);
    }

    // printf("Philosopher [%d] is eating\n", id);

    pthread_mutex_unlock(left_baguette);
    pthread_mutex_unlock(right_baguette);
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
    pthread_mutex_t *left_baguette = arg_philosopher->left_baguette;
    pthread_mutex_t *right_baguette = arg_philosopher->right_baguette;

    for (int i = 0; i < 5; i++)
    {
        // Philosopher thinks
        philosopher_thinking(id);

        // Philosopher eats
        philosopher_eating(id, rightGreater, left_baguette, right_baguette);
    }

    return NULL;
}


int main(int argc, char *argv[])
{
    int nbThreads = atoi(argv[1]);
    const int NB_PHILOSOPHERS = nbThreads;

    if (NB_PHILOSOPHERS <= 0) return EXIT_FAILURE;

    pthread_t philosophers[NB_PHILOSOPHERS];
    pthread_mutex_t baguettes[NB_PHILOSOPHERS];

    for (int i = 0; i < NB_PHILOSOPHERS; i++)
    {
        if (pthread_mutex_init(&baguettes[i], NULL) != 0)
        {
            perror("pthread_mutex_init()");
            return EXIT_FAILURE;
        }
    }

    bool rightGreater;
    int i = 0; // Important because i need to be valid outside the loop !

    for (i = 0; i < NB_PHILOSOPHERS; i++)
    {
        rightGreater = ((i + 1) % NB_PHILOSOPHERS > i) ? true : false;
        void *args = create_arg_philosopher(i, rightGreater, &baguettes[i], &baguettes[(i + 1) % NB_PHILOSOPHERS]);
        if (args == NULL) return EXIT_FAILURE;

        if (pthread_create(&philosophers[i], NULL, &philosopher_function, args) != 0)
        {
            perror("pthread_create()");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NB_PHILOSOPHERS; i++)
    {
        if (pthread_join(philosophers[i], NULL) != 0)
        {
            perror("pthread_join()");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}