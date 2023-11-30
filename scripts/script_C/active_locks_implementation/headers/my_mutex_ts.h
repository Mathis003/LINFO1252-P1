#ifndef MY_MUTEX_TS_H
#define MY_MUTEX_TS_H

#include <stdio.h>
#include <stdlib.h>

struct my_mutex {
    int todo;
} typedef my_mutex_t;

int my_mutex_init(my_mutex_t *my_mutex);

int my_mutex_destroy(my_mutex_t *my_mutex);

int my_mutex_lock(my_mutex_t *my_mutex);

int my_mutex_unlock(my_mutex_t *my_mutex);

#endif // MY_MUTEX_TS_H