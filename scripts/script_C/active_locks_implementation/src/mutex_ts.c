#include "../headers/test_and_set.h"
// mutex_ts


//! pour compiler: gcc main_mutex_ts.c -o main_mutex_ts -lpthread

// lock: ; étiquette, variable
//     .long 0 ; initialisée à 0
volatile long lock = 0;
int my_ts_mutex_init()
{
    // TODO
    return 0;
}

int my_ts_mutex_destroy()
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
int my_ts_mutex_lock()
{
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
}

// leave:
//     movl $0, %eax       ; %eax=0
//     xchgl %eax, (lock)  ; instruction atomique
//     ret
int my_ts_mutex_unlock()
{
    long eax;
    asm volatile(
        "movl $0, %%eax \n\t"
        "xchgl %%eax, %0"
                        
        : "+m" (lock), "=a" (eax)
    );
    return eax;
}