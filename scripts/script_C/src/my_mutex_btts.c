#include "../headers/my_mutex_btts.h"


void my_mutex_init(my_mutex_t *my_mutex)
{
    my_mutex->lock = 0; // Set lock to 0 (=free)
}


void my_mutex_destroy(my_mutex_t *my_mutex)
{
    my_mutex = NULL; // Make my_mutex unusable
}


int my_mutex_lock(my_mutex_t *my_mutex, int time_max_usec)
{
    int result;
    int incr = 2;
    while (my_mutex->lock == 1)
    {
        time = incr * incr;
        if (time > time_max_usec) time = time_max_usec;
        else                      incr++;
        usleep(time);
    }
    
    asm volatile("enter:\n\t"        // label "enter"
                 "xchg %0, %1\n\t"   // Exchange my_mutex->lock with 1 (atomic instruction)
                 "testl %1, %1\n\t"  // AND operation => set flag to the result
                 "jnz enter\n\t"     // flag != 0 => Jump label "enter"

                 :"=m"(my_mutex->lock), "=a"(result) // %0 = my_mutex->lock, %1 = result
                 :"a"(1), "m"(my_mutex->lock)        // Initialization : %1 set to 1, %0 set to my_mutex->lock
    );
    return result;
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