#include "../headers/my_mutex_tts.h"

void my_mutex_init(my_mutex_t *my_mutex)
{
    my_mutex->lock = 0; // Set lock to 0 (=free)
}

void my_mutex_destroy(my_mutex_t *my_mutex)
{
    my_mutex = NULL; // Make my_mutex unusable
}

int my_mutex_lock(my_mutex_t *my_mutex)
{
    int result;
    asm volatile("while_locked:\n\t"     // label "while_locked"
                 "testl %1, %0\n\t"      // AND operation => set flag to the result
                 "jnz while_locked\n\t"  // flag != 0 => Jump label "while_locked"

                 "enter:\n\t"            // label "enter"
                 "xchg %0, %1\n\t"       // Exchange my_mutex->lock with 1 (atomic instruction)
                 "testl %1, %1\n\t"      // AND operation => set flag to the result
                 "jnz enter\n\t"         // flag != 0 => Jump label "enter"

                 :"=m"(my_mutex->lock), "=a"(result)  // %0 = my_mutex->lock, %1 = result
                 :"a"(1), "m"(my_mutex->lock)         // Initialization : %1 set to 1, %0 set to my_mutex->lock
    );
    return result;
}

int my_mutex_unlock(my_mutex_t* my_mutex)
{
    int result;
    asm volatile("xchg %0, %1\n\t"  // Exchange my_mutex->lock with 0 (atomic instruction)
                 :"=m"(my_mutex->lock), "=a"(result)  // %0 = my_mutex->lock, %1 = result
                 :"a"(0), "m"(my_mutex->lock)         // Initialization : %1 set to 0, %0 set to my_mutex->lock
    );
    return result;
}