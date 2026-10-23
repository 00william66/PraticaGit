#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
/* Executes the process status command with all-user, detailed, unattached flags */
    system("ls");
    return 0;
}

/*

willy@GIGABYTE-G5-W$ gcc -Wall myPS.c -o myPS
willy@GIGABYTE-G5-W$ ./myPS

*/