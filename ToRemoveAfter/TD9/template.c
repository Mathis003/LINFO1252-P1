#include <stdio.h>

/* Code C
* if(*a > 10) 
*   *a = b + 3;
* else 
*   *a = c - 4;
*/

static inline void my_inline_func(int *a, int b, int c)
{
    __asm__( "cmpl $10, %0\n\t"
            "jle PART_2\n\t"
            "addl $3, %1\n\t"
            "movl %1, %0\n\t"
            "jmp END\n\t"
            "PART_2:\n\t"
            "subl $4, %2\n\t"
            "movl %2, %0\n\t"
            "END:\n\t"
            : "+m" (*a)
            : "r" (b), "r" (c));
}

int main()
{
    int a = 11, b = 2, c = 3;
    my_inline_func(&a, b, c);
    printf("a = %d ; expected : %d \n", a, 5);

    a = 8, b = 2, c = 3;
    my_inline_func(&a, b, c);
    printf("a = %d ; expected : %d \n", a, -1);

    a = 42, b = 12, c = 50;
    my_inline_func(&a, b, c);
    printf("a = %d ; expected : %d \n", a, 15);

    a = 0, b = 12, c = 50;
    my_inline_func(&a, b, c);
    printf("a = %d ; expected : %d \n", a, 46); 
    
    a = 10, b = 1, c = 2;	
    my_inline_func(&a, b, c);
    printf("a = %d ; expected : %d \n", a, -2);

    return 0;
}
