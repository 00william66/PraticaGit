#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#define FIFO_PATH "/tmp/fifo_pipe"

int main(void){

    int fd;
    int number;

    if (mkfifo(FIFO_PATH, 0666) == -1) {
    if (errno != EEXIST) {
        perror("Erro grave no mkfifo");
        return 1;
    }
}

    printf("Producer: Waiting for consumer to open fifo...\n");
    fd = open(FIFO_PATH, O_WRONLY);

    if(fd == -1){
        perror("Error opening fifo to write\n");
        return 1;
    }

    printf("Producer ready -> insert temperatures:\n");

    while(scanf("%d", &number) == 1){
        
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