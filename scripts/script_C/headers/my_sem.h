#ifndef MY_SEM_H
#define MY_SEM_H

#include <stdio.h>
#include <stdlib.h>

#include "my_mutex_ts.h"

typedef struct my_sem {
    int value;
    my_mutex_t *mutex;
} my_sem_t;

int my_sem_init(my_sem_t *sem, unsigned int value);

int my_sem_destroy(my_sem_t *sem);

int my_sem_wait(my_sem_t *sem);

int my_sem_post(my_sem_t *sem);

#endif // MY_SEM_H