#include "../headers/my_mutex_tts.h"

void my_mutex_init(my_mutex_t *my_mutex)
{
    my_mutex->lock = 0; // Set lock to 0 (=free)
}

void my_mutex_destroy(my_mutex_t *my_mutex)
{
    my_mutex = NULL; // Make my_mutex unusable
}

void exch(volatile int *lock_value, int *result)
{
    asm volatile("xchg %0, %1\n\t"
                 :"+m" (*lock_value), "+r" (*result));
}

int my_mutex_lock(my_mutex_t *my_mutex)
{
    while (my_mutex->lock == 1) {};

    int result = 1;
    while (1)
    {
        exch(&(my_mutex->lock), &result);
        if (result != 1) break;
    }
    return result;
}

int my_mutex_unlock(my_mutex_t* my_mutex)
{
    int result = 0;
    exch(&(my_mutex->lock), &result);
    return result;
}