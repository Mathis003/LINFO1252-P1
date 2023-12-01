#include "../headers/my_mutex_ts.h"


void my_mutex_init(my_mutex_t *my_mutex)
{
    my_mutex->lock = 0;
}


void my_mutex_destroy(my_mutex_t *my_mutex)
{
    my_mutex->lock = 0;
    my_mutex = NULL;
}


int my_mutex_lock(my_mutex_t *my_mutex)
{
    int ret;
    asm volatile("enter:;"
        "xchg %0, %1;"
        "testl %1, %1;"
        "jnz enter;"

        :"=m"(my_mutex->lock), "=a"(ret)
        :"a"(1), "m"(my_mutex->lock)
    );
    return ret;
}

int my_mutex_unlock(my_mutex_t *my_mutex)
{
    int ret;
    asm volatile("xchg %0, %1;"
        :"=m"(my_mutex->lock), "=a"(ret)
        :"a"(0), "m"(my_mutex->lock)
    );
    return ret;
}

/*
int my_mutex_lock(my_mutex_t *my_mutex)
{
    int eax;
    asm volatile(
        "1:\n\t"
        "movl $1, %%eax\n\t"
        "xchgl %%eax, %0\n\t"
                                    
        "testl %%eax, %%eax\n\t"
        "jnz 1b"
        : "+m" (my_mutex->lock), "=a" (eax)
        :
        : "cc"
    );
    return eax;
}


int my_mutex_unlock(my_mutex_t *my_mutex)
{
    int eax;
    asm volatile(
        "movl $0, %%eax\n\t"
        "xchgl %%eax, %0"
                        
        : "+m" (my_mutex->lock), "=a" (eax)
    );
    return eax;
}
*/