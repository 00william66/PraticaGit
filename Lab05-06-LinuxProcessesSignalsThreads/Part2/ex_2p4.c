#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if(argc < 3 || atoi(argv[2]) < 1 || atoi(argv[2]) > 99){
        printf("Usage: %s <Group> <Number of Folders(1 to 99)> --Discard '<>'\n", argv[0]);
        return 1;
    }

    int i, status, nFolders = atoi(argv[2]);
    char confirm, folderName[256];

    for(i = 1; i <= nFolders; i++){

        /*Montar o nome da pasta para cada iteração*/
        snprintf(folderName, 256, "%s%d", argv[1], i);

        pid_t pid = fork(); /*Cria a cópia do processo*/

        if(pid < 0){

            perror("Ocurred an error while forking");
            continue;
        } else if(pid == 0){ /*Quer dizer que é o filho*/

            execlp("rmdir", "rmdir", folderName, NULL);
            exit(1); /* equivale ao return 1, quer dizer que não foi possivel remover a pasta*/

        } else {
            /*Espera que o rmdir termine*/
            wait(&status);

        }
        /*Verificar se rmdir falhou*/
        if(WIFEXITED(status) && WEXITSTATUS(status) != 0){

            while(1){
                
                printf("\n%s%d Folder is not empty. Remove anyway?", argv[1], i);
                scanf(" %c", &confirm);

                if(confirm == 'y' || confirm == 'Y'){

                    pid_t pid2 = fork();
                    
                    if(pid2 < 0){
                        perror("Ocurred an error while forking");
                        break;

                    } else if(pid2 == 0){ /*Quer dizer que é o filho*/
                        execlp("rm", "rm", "-r", folderName, NULL);
                        exit(1); /* equivale ao return 1, quer dizer que não foi possivel remover a pasta*/

                    } else {
                        /*Espera que o rmdir termine*/
                        wait(NULL); /*Aqui como forcei a remover a pasta não preciso de confirmar se ele conseguiu
                        removê-la. Estaa linha apenas espera que o filho termine mas descarta o codigo de saida do rm -r
                        pois não é informação necessária*/

                    }
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