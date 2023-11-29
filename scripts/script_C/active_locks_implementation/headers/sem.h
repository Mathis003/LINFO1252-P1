#include <stdio.h>
#include <stdlib.h>

struct my_sem {
    // TODO
} typedef my_sem_t;

int my_sem_init(my_sem_t *sem, int pshared, unsigned int value);

int my_sem_destroy(my_sem_t *sem);

int my_sem_wait(my_sem_t *sem);

int my_sem_post(my_sem_t *sem);