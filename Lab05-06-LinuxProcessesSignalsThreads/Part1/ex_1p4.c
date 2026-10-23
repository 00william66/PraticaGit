#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*LEMBRAR QUE ESTE  EXERCICIO É UM COMPLEMENTO AO 1.3*/

int main(int argc, char *argv[]){
    if(argc < 3 || atoi(argv[2]) < 1 || atoi(argv[2]) > 99){
        printf("Usage: %s <Group> <Number of Folders(1 to 99)> --Discard '<>'\n", argv[0]);
        return 1;
    }

    int i, status, nFolders = atoi(argv[2]);
    char confirm, command[256];
    
    for(i = 1; i <= nFolders; i++){
        
        snprintf(command, sizeof(command), "rmdir %s%d", argv[1], i);
        status = system(command);

        if(status != 0){
            
            while (1)
            {
                printf("\n%s%d Folder is not empty. Remove anyway?", argv[1], i);
                scanf(" %c", &confirm);
    
                if(confirm == 'y' || confirm == 'Y'){
                    snprintf(command, sizeof(command), "rm -r %s%d", argv[1], i);
                    system(command);
                    break;
                } else if(confirm == 'n' || confirm == 'N'){
                    break;
                } else {
                    printf("BROU, Y/y or n/N\n");
                }
            }
            
            
        }

    }
    return 0;
}

