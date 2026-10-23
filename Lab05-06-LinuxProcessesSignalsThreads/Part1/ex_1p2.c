#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    } 

    char command[256];

    snprintf(command, sizeof(command), "wc -wm %s", argv[1]);

    system(command);
}