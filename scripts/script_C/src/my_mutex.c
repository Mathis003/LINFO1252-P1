#include "../headers/my_mutex.h"

void my_mutex_init(my_mutex_t *my_mutex)
{
    my_mutex->lock = 0;
}


void my_mutex_destroy(my_mutex_t *my_mutex)
{
    my_mutex = NULL;
}


void exch(volatile int *lock_value, int *result)
{
    asm volatile("xchg %0, %1\n\t"
                 :"+r" (*result), "+m" (*lock_value));
}

int my_mutex_lock(my_mutex_t *my_mutex)
{  
    int result = 1;
    do
    {
        #ifdef TTS_MUTEX

        while (my_mutex->lock == 1) {};

        #elif BTTS_MUTEX

        int time_max_usec = 50;
        int incr = 1;
        int time;
        while (my_mutex->lock == 1)
        {
            time = incr * incr;
            if (time > time_max_usec) time = time_max_usec;
            else                      incr++;
            usleep(time);
        }

        #endif
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
