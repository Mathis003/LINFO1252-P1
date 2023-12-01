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

void my_sem_destroy(my_sem_t *sem)
{
    my_mutex_destroy(sem->mutex);
    free(sem->mutex);
    sem = NULL;
}

int my_sem_wait(my_sem_t *sem)
{
    while (1)
    {
        if (lock_mutex(sem->mutex) != 0) return EXIT_FAILURE;
        if (sem->value <= 0)
        {
            if (unlock_mutex(sem->mutex) != 0) return EXIT_FAILURE;
        }
        else
        {
            (sem->value)--;
            if (unlock_mutex(sem->mutex) != 0) return EXIT_FAILURE;
            break;
        }
    }
    return EXIT_SUCCESS;
}

int my_sem_post(my_sem_t *sem)
{
    if (lock_mutex(sem->mutex) != 0) return EXIT_FAILURE;
    (sem->value)++;
    if (unlock_mutex(sem->mutex) != 0) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}