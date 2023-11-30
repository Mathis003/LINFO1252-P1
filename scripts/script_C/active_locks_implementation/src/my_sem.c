#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> 

struct my_sem {
    // TODO
} typedef my_sem_t;

int my_sem_init(my_sem_t *sem, int pshared, unsigned int value)
{
    // TODO
    return 0;
}

int my_sem_destroy(my_sem_t *sem)
{
    // TODO
    return 0;
}

int my_sem_wait(my_sem_t *sem)
{
    return 0;
}

int my_sem_post(my_sem_t *sem)
{
    return 0;
}