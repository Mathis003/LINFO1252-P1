#include "../headers/my_mutex_ts.h"


int my_mutex_init(my_mutex_t *my_mutex)
{
    my_mutex->lock = 0;
    return EXIT_SUCCESS;
}


int my_mutex_destroy(my_mutex_t *my_mutex)
{
    my_mutex->lock = 0;
    my_mutex = NULL;
    return EXIT_SUCCESS;
}

int counter = 0;
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
    int eax;
    asm volatile(
        "1: \n\t"
        "movl $1, %%eax \n\t"
        "xchgl %%eax, %0 \n\t"
                                    
        "testl %%eax, %%eax \n\t"
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
        "movl $0, %%eax \n\t"
        "xchgl %%eax, %0"
                        
        : "+m" (my_mutex->lock), "=a" (eax)
    );
    return eax;
}