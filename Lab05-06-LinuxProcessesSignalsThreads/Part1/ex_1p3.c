#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc < 3 || atoi(argv[2]) < 1 || atoi(argv[2]) > 99){
        printf("Usage: %s <Group> <Number of Folders(1 to 99)> --Discard '<>'\n", argv[0]);
        return 1;
    }

    int nFolders = atoi(argv[2]), i;
    char command[256];
    
    for (i = 1; i <= nFolders; i++){
        snprintf(command, sizeof(command), "mkdir %s%d", argv[1], i);
        system(command);
    }
    return 0;
}

/*willy@GIGABYTE-G5-W$ gcc -Wall ex_1p3.c -o createFolders*/
/*willy@GIGABYTE-G5-W$ ./createFolders Group 12*/