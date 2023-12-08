#include "../headers/my_sem.h"

void my_sem_init(my_sem_t *sem, unsigned int value)
{
    sem->mutex = (my_mutex_t *) malloc(sizeof(my_mutex_t));
    my_mutex_init(sem->mutex);
    sem->value = value;
}

void my_sem_destroy(my_sem_t *sem)
{
    my_mutex_destroy(sem->mutex);
    free(sem->mutex);
    sem = NULL;
}

void my_sem_wait(my_sem_t *sem)
{
    my_mutex_lock(sem->mutex);
    while (sem->value <= 0)
    {
        my_mutex_unlock(sem->mutex);
        my_mutex_lock(sem->mutex);
    }
    (sem->value)--;
    my_mutex_unlock(sem->mutex);
}

void my_sem_post(my_sem_t *sem)
{
    my_mutex_lock(sem->mutex);
    (sem->value)++;
    my_mutex_unlock(sem->mutex);
}