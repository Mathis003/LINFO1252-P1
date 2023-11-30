#include "../headers/my_mutex_ts.h"

//! pour compiler: gcc main_mutex_ts.c -o main_mutex_ts -lpthread

// lock: ; étiquette, variable
//     .long 0 ; initialisée à 0
volatile long lock = 0;
int my_mutex_init(my_mutex_t *my_mutex)
{
    // TODO
    return 0;
}

int my_mutex_destroy(my_mutex_t *my_mutex)
{
    // TODO
    return 0;
}


// enter:
//     movl $1, %eax ; %eax=1
//     xchgl %eax, (lock)  ; instruction atomique, échange (lock) et %eax
//                         ; après exécution, %eax contient la donnée qui était
//                         ; dans lock et lock la valeur 1
//     testl %eax, %eax    ; met le flag ZF à vrai si %eax contient 0
//     jnz enter ; retour à enter: si ZF n'est pas vrai
//     ret
int my_mutex_lock(my_mutex_t *my_mutex)
{
    /*
    long eax;
    asm volatile(
        "1: \n\t"
        "movl $1, %%eax \n\t"
        "xchgl %%eax, %0 \n\t"
                                    
        "testl %%eax, %%eax \n\t"
        "jnz 1b"
        : "+m" (lock), "=a" (eax)
        :
        : "cc"
    );
    return eax;
    */
   return 0;
}

// leave:
//     movl $0, %eax       ; %eax=0
//     xchgl %eax, (lock)  ; instruction atomique
//     ret
int my_mutex_unlock(my_mutex_t *my_mutex)
{
    /*
    long eax;
    asm volatile(
        "movl $0, %%eax \n\t"
        "xchgl %%eax, %0"
                        
        : "+m" (lock), "=a" (eax)
    );
    return eax;
    */
   return 0;
}