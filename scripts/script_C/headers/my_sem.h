#ifndef MY_SEM_H
#define MY_SEM_H

#include "my_mutex.h"

typedef struct my_sem {
    int value;
    my_mutex_t *mutex;
} my_sem_t;

void my_sem_init(my_sem_t *sem, unsigned int value);

void my_sem_destroy(my_sem_t *sem);

void my_sem_wait(my_sem_t *sem);

void my_sem_post(my_sem_t *sem);

#endif // MY_SEM_H