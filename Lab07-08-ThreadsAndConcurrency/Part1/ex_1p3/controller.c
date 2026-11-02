#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#define FIFO_PATH_CONT "/tmp/fifo_cc" /*consumer->controller*/

int main(void){
    int fd;
    float average;

    if(mkfifo(FIFO_PATH_CONT, 0666) == -1){
        if(errno != EEXIST){
            perror("Error in mkfifo\n");
            return 1;
        }
    }


    printf("Consumer: Waiting for consumer to open fifo...\n");
    fd = open(FIFO_PATH_CONT, O_RDONLY);
    if(fd == -1){
        perror("Error openinf fifo to write\n");
        return 1;
    }

    printf("Controller ready -> Waiting for data to print...\n");
    while(read(fd, &average, sizeof(float)) > 0){
        printf("\nFiltered temperature: %.2f ºC\n", average);
        if(average < 80){
            printf("Não está chuve nem orvalho, mas está um frio do...\n");
        } else if(average >= 80 && average < 95){
            printf("Bom temperatura nengue\n");
        } else if(average > 95){
            printf("TA PEGANDO FOGO BICHO\n");
        }

    }


    close(fd);
    unlink(FIFO_PATH_CONT);
    printf("Terminating controller...\n");
    return 0;
}