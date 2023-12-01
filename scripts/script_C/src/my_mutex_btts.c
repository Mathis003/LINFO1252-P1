#include "../headers/my_mutex_btts.h"


void my_mutex_init(my_mutex_t *my_mutex)
{
    my_mutex->lock = 0;
}


void my_mutex_destroy(my_mutex_t *my_mutex)
{
    my_mutex->lock = 0;
    my_mutex = NULL;
}


int my_mutex_lock(my_mutex_t *my_mutex, int time_usec)
{
    int ret;
    int i=2;
    while (my_mutex->lock == 1)
    {
        if(i^2 > time_usec) usleep(time_usec);
        else
        {
            usleep(i^2);
            i++;
        }
    }
    asm volatile(
        "atomic:;"
        "xchg %0, %1;"
        "testl %1, %1;"
        "jnz atomic;"

        :"=m"(my_mutex->lock), "=a"(ret)
        :"a"(1), "m"(my_mutex->lock
    ));
    return ret;
}

int my_mutex_unlock(my_mutex_t *my_mutex)
{
    int ret;
    asm("xchg %0, %1;"

        :"=m"(my_mutex->lock), "=a"(ret)
        :"a"(0), "m"(my_mutex->lock)
    );
    return ret;
}

/*
int my_mutex_lock(my_mutex_t *my_mutex)
{
    // TODO
    return 0;
}

int my_mutex_unlock(my_mutex_t *my_mutex)
{
    // TODO
    return 0;
}
*/