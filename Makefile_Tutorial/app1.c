#include <stdio.h>
#include "part1.h"

void f2(void);

int main(void)
{
    f1();
    f2();
    return 0;
}

void f2(void)
{
    printf("This is f2\n");
    



}

/*
willy@GIGABYTE-G5-W$ gcc -Wall -c part1.c
willy@GIGABYTE-G5-W$ gcc -Wall -c app1.c
willy@GIGABYTE-G5-W$ gcc -o app1 app1.o part1.o
willy@GIGABYTE-G5-W$ ./app1
This is f1
This is f2
*/