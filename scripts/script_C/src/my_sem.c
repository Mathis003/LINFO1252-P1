#include "../headers/my_sem.h"

int my_sem_init(my_sem_t *sem, unsigned int value)
{
    sem->mutex = (my_mutex_t *) malloc(sizeof(my_mutex_t));
    if (sem->mutex == NULL)
    {
        perror("malloc()");
        return EXIT_FAILURE;
    }
    my_mutex_init(sem->mutex);
    sem->value = value;
    return EXIT_SUCCESS;
}

int my_sem_destroy(my_sem_t *sem)
{
    my_mutex_destroy(sem->mutex);
    free(sem->mutex);
    sem = NULL;
    return EXIT_SUCCESS;
}

int my_sem_wait(my_sem_t *sem)
{
    while (1)
    {
        lock_mutex(sem->mutex);
        if (sem->value <= 0) unlock_mutex(sem->mutex);
        else
        {
            (sem->value)--;
            unlock_mutex(sem->mutex);
            break;
        }
    }
    return EXIT_SUCCESS;
}

int my_sem_post(my_sem_t *sem)
{
    lock_mutex(sem->mutex);
    (sem->value)++;
    unlock_mutex(sem->mutex);
}