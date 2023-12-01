#include "../headers/my_mutex_ts.h"
#include <stdatomic.h>

//! pour compiler: gcc main_mutex_ts.c -o main_mutex_ts -lpthread

// lock: ; étiquette, variable
//     .long 0 ; initialisée à 0


int my_mutex_init(my_mutex_t **my_mutex)
{
    *my_mutex = malloc(sizeof(my_mutex_t));
    
    if (*my_mutex == NULL) {
        return -1;
    }

    (*my_mutex)->lock = 0;
    
    return 0;
}


int my_mutex_destroy(my_mutex_t *my_mutex)
{
    free(my_mutex);
    // TODO
    return 0;
}

long counter = 0;
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
    // if (my_mutex == NULL) {
    //     return -1;
    // }
    // counter++;
    // // printf("my_mutex_lock: %d\n", my_mutex->lock);
    // printf("before asm, my_mutex->lock: %ld, counter: %d\n", my_mutex->lock, counter);
    // int ret;
    // asm(
    //     "enter: \n\t" // Label for the start of the loop
    //     "xchgl %0, %1 \n\t" // Exchange the values of the memory location pointed to by my_mutex->lock and the register %1 (which is eax)
    //     "testl %1, %1 \n\t" // Test the value in %1 (eax). This sets the zero flag if eax is zero
    //     "jnz enter" // Jump back to the "enter" label if the zero flag is not set, i.e., if eax is not zero
    //     : "=m" (my_mutex->lock), "=a" (ret) // Output operands: my_mutex->lock is assigned to %0, and ret is assigned to %1 (eax)
    //     : "a" (1), "m" (my_mutex->lock) // Input operands: 1 is loaded into eax, and the memory location pointed to by my_mutex->lock is loaded into memory
    // );
    // // printf("my_mutex_lock exit: %d\n", my_mutex->lock);
    // printf("after asm, my_mutex->lock: %ld, counter: %d\n", my_mutex->lock, counter);
    // return ret;
    

    if (my_mutex == NULL) {
        return -1;
    }
    counter++;
    printf("before asm, my_mutex->lock: %ld, counter: %d\n", my_mutex->lock, counter);
    
    int ret;
    do {
        ret = atomic_exchange(&my_mutex->lock, 1);
    } while (ret != 0);
    
    printf("after asm, my_mutex->lock: %ld, counter: %d\n", my_mutex->lock, counter);
    return 0;
}

int my_mutex_unlock(my_mutex_t *my_mutex)
{
    // if (my_mutex == NULL) {
    //     return -1;
    // }
    // printf("my_mutex_unlock: %d\n", my_mutex->lock);
    
    
    // int eax;
    // asm(
    //     "xchgl %0, %1;"
    //     : "=m" (my_mutex->lock), "=a" (eax)
    //     : "a" (0), "m" (my_mutex->lock)
    // );

    // // printf("my_mutex_unlock exit: %d\n", my_mutex->lock);
    
    // return eax;
    

    // if (my_mutex == NULL) {
    //     return -1;
    // }

    int eax = atomic_exchange(&my_mutex->lock, 0);

    return 0;
}


