#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_PATH "/tmp/my_fifo"

int main(void) {
    int fd;
    int number;

    /*Criar fifo se ainda não existir*/
    if((mkfifo(FIFO_PATH, 0666) == -1)){ /*Permite leitura e escrita*/
        perror("Error in mkfifo\n");
    }
    printf("Producer: Waiting for consumer to open fifo...\n");
    fd = open(FIFO_PATH, O_WRONLY);

    if(fd == -1){
        perror("Error opening fifo to write\n");
        return 1;
    }

    printf("Producer ready -> insert integers:\n");
    
    while(scanf("%d", &number) == 1){  /*verificar se foi introduzido um numero valido
                                        (neste caso um inteiro %d) não quero cá virgulas*/
        if(write(fd, &number, sizeof(int)) == -1){
            perror("Error writing in fifo\n");
            break;
        }

    }

    close(fd);
    unlink(FIFO_PATH);
    printf("Terminating producer...\n");
    return 0;
}