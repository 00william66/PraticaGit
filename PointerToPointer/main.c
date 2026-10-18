#include <stdio.h>

int main(void)
{
    int x = 5;
    int *ptr_x;    /*Ponteiro para x*/
    int **ptr_ptr_x;   /*Ponteiro para ponteiro de x*/

    /*Inicialização dos ponteiros*/

    ptr_x = &x;
    ptr_ptr_x = &ptr_x;

    printf("x = %d &x = %p\n", x, (void*)&x);
    printf("x = %d &x = %p\n", *ptr_x, (void*)ptr_x);
    printf("x = %d &x = %p\n", **ptr_ptr_x, (void*)*ptr_ptr_x);

    return 0;
}

/*
willy@GIGABYTE-G5-W$ gcc -Wall -c main.c
willy@GIGABYTE-G5-W$ gcc -o main main.o
willy@GIGABYTE-G5-W$ ./main
x = 5 &x = 0x7ffd558aee94
x = 5 &x = 0x7ffd558aee94
x = 5 &x = 0x7ffd558aee94

*/