#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#define FIFO_PATH "/tmp/fifo_pc"
#define FIFO_PATH_CONT "/tmp/fifo_cc" /*cartão de cidadão, brincadeira, fifo consumidor->cotrolador*/


int main(void){
    int fd, fd2, newTemp;
    int window[5];
    int divider, i = 0, count = 0;
    float sum = 0, average = 0;

    if(mkfifo(FIFO_PATH, 0666) == -1){
        if(errno != EEXIST){
            perror("Error in mkfifo\n");
            return 1;
        }
    }

    printf("Consumer: Waiting for producer to open fifo PC...\n");
    fd = open(FIFO_PATH, O_RDONLY);
    if(fd == -1){
        perror("Error opening fifo PC to write\n");
        return 1;
    }

    if(mkfifo(FIFO_PATH_CONT, 0666) == -1){
        if(errno != EEXIST){
            perror("Error in mkfifo\n");
            return 1;
        }
    }

    printf("Consumer: Waiting for controller to open fifo CC...\n");
    fd2 = open(FIFO_PATH_CONT, O_WRONLY);
    if(fd2 == -1){
        perror("Error opening fifo CC to write\n");
        return 1;
    }



    printf("Consumer ready -> Waiting for data to send to the controller...\n");
    while(read(fd, &newTemp, sizeof(int)) > 0){
        count++;

        if(count <= 5){
            window[count-1] = newTemp;
            divider = count;
        } else {
            for(i = 0; i < 4; i++){
                window[i] = window[i+1];
            }
            window[4] = newTemp;
            divider = 5;
        }

        sum = 0;
        for(i = 0; i < divider; i++){
            sum += window[i];
        }
        average = sum / divider;
        printf("Filtered temperature: %.2f ºC\n", average);

        if(write(fd2, &average, sizeof(float)) == -1){
            perror("Error wrinting if fifo CC\n");
            break;
        }

    }
    close(fd);
    unlink(FIFO_PATH);
    close(fd2);
    unlink(FIFO_PATH_CONT);
    printf("Terminating consumer and controller...\n");
}