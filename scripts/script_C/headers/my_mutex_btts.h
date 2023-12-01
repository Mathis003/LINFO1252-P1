#ifndef MY_MUTEX_BTSS_H
#define MY_MUTEX_BTSS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <unistd.h>


typedef struct my_mutex {
    volatile int lock;
} my_mutex_t;

void my_mutex_init(my_mutex_t *my_mutex);

void my_mutex_destroy(my_mutex_t *my_mutex);

int my_mutex_lock(my_mutex_t *my_mutex, int time_usec);

int my_mutex_unlock(my_mutex_t *my_mutex);

#endif // MY_MUTEX_BTSS_H