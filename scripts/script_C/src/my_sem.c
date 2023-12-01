#include "../headers/my_sem.h"


int my_sem_init(my_sem_t *sem, unsigned int value)
{
    sem = (my_sem_t *) malloc(sizeof(my_sem_t));
    if (sem == NULL)
    {
        perror("malloc()");
        return EXIT_FAILURE;
    }
    sem->mutex = (my_mutex_t *) malloc(sizeof(my_mutex_t));
    if (sem->mutex == NULL)
    {
        perror("malloc()");
        return EXIT_FAILURE;
    }
    sem->mutex->lock = 0;
    sem->value = value;
    return EXIT_SUCCESS;
}

int my_sem_destroy(my_sem_t *sem)
{
    free(sem->mutex);
    free(sem);
    return EXIT_SUCCESS;
}

int my_sem_wait(my_sem_t *sem)
{
    while (sem->value <= 0);
    lock_mutex(sem->mutex->lock);
    (sem->value)--;
    unlock_mutex(sem->mutex->lock);
}

int my_sem_post(my_sem_t *sem)
{
    lock_mutex(sem->mutex->lock);
    (sem->value)++;
    unlock_mutex(sem->mutex->lock);
}