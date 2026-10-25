#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    if(argc < 3 || atoi(argv[2]) < 1 || atoi(argv[2]) > 99){
        printf("Usage: %s <Group> <Number of Folders(1 to 99)> --Discard '<>'\n", argv[0]);
        return 1;
    }

    int i, nFolders = atoi(argv[2]);
    char *args[nFolders + 2]; /*programa + null*/
    
    args[0] = "mkdir";

    for(i = 1; i <= nFolders; i++){
        args[i] = (char  *)malloc(256 * sizeof(char));
        snprintf(args[i], 256, "%s%d", argv[1], i);
    }

    args[nFolders + 1] = NULL;

    execvp("mkdir", args);
    perror("Error while executing execvp");
    
    for(i = 1; i < nFolders; i++){
        free(args[i]);
    }

    return 1;


    
}