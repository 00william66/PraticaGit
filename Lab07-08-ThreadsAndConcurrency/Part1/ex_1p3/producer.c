#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#define FIFO_PATH "/tmp/fifo_pc" /*Producer -> Consumer*/

int main(void){
    int fd, number;
    
    if(mkfifo(FIFO_PATH, 0666) == -1){
        if(errno != EEXIST){
            perror("Error in mkfifo\n");
            return 1;
        }
    }

    printf("Producer PC: Waiting for consumer to open fifo PC...\n");
    fd = open(FIFO_PATH, O_WRONLY);

    if(fd == -1){
        perror("Error opening fifo PC to write\n");
    }

    printf("Producer ready -> insert temperatures: \n");

    while(scanf("%d", &number) == 1){

        if(write(fd, &number, sizeof(int)) == -1){
            perror("Error wrinting if fifo PC\n");
            break;
        }
    }

    close(fd);
    unlink(FIFO_PATH);
    printf("Terminating producer...\n");
    return 0;
}

/*CTRL+D TO TERMINATE*/