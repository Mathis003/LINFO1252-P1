#include "../headers/my_mutex_ts.h"

//! pour compiler: gcc main_mutex_ts.c -o main_mutex_ts -lpthread

// lock: ; étiquette, variable
//     .long 0 ; initialisée à 0


int my_mutex_init(my_mutex_t *my_mutex)
{
    my_mutex->lock = 0;
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
    if (my_mutex == NULL) {
        return -1;
    }

    printf("my_mutex_lock: %d\n", my_mutex->lock);
    
    long eax;
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
    // printf("my_mutex_lock exit: %d\n", my_mutex->lock);
    
    return 0;
    
}

int my_mutex_unlock(my_mutex_t *my_mutex)
{
    if (my_mutex == NULL) {
        return -1;
    }
    printf("my_mutex_unlock: %d\n", my_mutex->lock);
    
    
    long eax;
    asm volatile(
        "movl $0, %%eax \n\t"
        "xchgl %%eax, %0"
                        
        : "+m" (my_mutex->lock), "=a" (eax)
    );

    // printf("my_mutex_unlock exit: %d\n", my_mutex->lock);
    
    return 0;
    
}