#include "../headers/my_mutex.h"

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
    #ifdef BTTS_MUTEX

    int incr = 2;
    int time_max_usec = 50; // Seems to be optimal (test done)
    int time;

    while (my_mutex->lock == 1)
    {
        time = incr * incr;
        if (time > time_max_usec) time = time_max_usec;
        else                      incr++;
        usleep(time);
    }

    #elif TTS_MUTEX

    while (my_mutex->lock == 1) {};

    #endif

    int result = 1;
    do
    {
        exch(&(my_mutex->lock), &result);
    } while (result == 1);

    return result;
}

int my_mutex_unlock(my_mutex_t* my_mutex)
{
    int result = 0;
    exch(&(my_mutex->lock), &result);
    return result;
}