#include "../headers/philosopher.h"

void *create_arg_philosopher(int id, void *left_baguette, void *right_baguette)
{
    args_philosopher_t *args_philosopher = malloc(sizeof(args_philosopher_t));
    args_philosopher->id = id;
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
    void *left_baguette = arg_philosopher->left_baguette;
    void *right_baguette = arg_philosopher->right_baguette;
    bool rightGreater = ((id + 1) % NB_PHILOSOPHERS > id) ? true : false;

    for (int i = 0; i < 1000000; i++)
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

    NB_PHILOSOPHERS = atoi(argv[1]);

    if (NB_PHILOSOPHERS <= 1)
    {
        perror("NB_PHILOSOPHERS <= 1");
        return EXIT_FAILURE;
    }

    pthread_t philosophers[NB_PHILOSOPHERS];

    #ifdef POSIX
    pthread_mutex_t baguettes[NB_PHILOSOPHERS];
    #else
    my_mutex_t baguettes[NB_PHILOSOPHERS];
    #endif

    for (int i = 0; i < NB_PHILOSOPHERS; i++) init_mutex(&baguettes[i]);
    for (int i = 0; i < NB_PHILOSOPHERS; i++) pthread_create(&philosophers[i], NULL, philosopher_function, create_arg_philosopher(i, &baguettes[i], &baguettes[(i + 1) % NB_PHILOSOPHERS]));
    for (int i = 0; i < NB_PHILOSOPHERS; i++) pthread_join(philosophers[i], NULL);
    for (int i = 0; i < NB_PHILOSOPHERS; i++) destroy_mutex(&baguettes[i]);
    
    return EXIT_SUCCESS;
}