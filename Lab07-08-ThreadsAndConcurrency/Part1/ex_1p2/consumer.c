#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>


#define FIFO_PATH "/tmp/fifo_pipe"

int main(void){
    int fd;
    int newTemp;
    int window[5];
    int i=0, divider, count = 0;
    float sum = 0, average = 0;

    if (mkfifo(FIFO_PATH, 0666) == -1) {
    if (errno != EEXIST) {
        perror("Erro grave no mkfifo");
        return 1;
    }
}

    printf("Consumer: Waiting for producer to open fifo...\n");
    fd = open(FIFO_PATH, O_RDONLY);
    if(fd == -1){
        perror("Error opening fifo to read\n");
        return 1;
    }


    printf("Consumer ready -> Waiting for data to print...\n");
    while (read(fd, &newTemp, sizeof(int)) > 0) {
    
    count++;
    
    if (count <= 5) {
        window[count - 1] = newTemp; 
        divider = count;
    } else {
        for (i = 0; i < 4; i++) {
            window[i] = window[i + 1];
        }
        window[4] = newTemp; 
        divider = 5;
    }

    sum = 0;
    for (i = 0; i < divider; i++) {
        sum += window[i];
    }

    average = sum / divider;
    printf("Filtered temperature: %.2f ºC\n", average);
}
    close(fd);
    unlink(FIFO_PATH);
    printf("Terminating consumer...\n");
    return 0;
}

