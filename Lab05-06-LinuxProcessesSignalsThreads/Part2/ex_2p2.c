#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    execlp("wc", "wc", "-wm", argv[1], NULL);
    perror("Error while execcuting execlp");
    return 1; /*ao executar o exec, o programa atual é 
    substituido pelo programa executado pelo exec*/
    
}