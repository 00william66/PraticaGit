#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <err.h>
#include <sys/mman.h>

#define BUFFER_SIZE 10

typedef struct{
    uint16_t buffer[BUFFER_SIZE];
    unsigned int in;
    unsigned int out;
}SharedBuffer;

int main(int argc, char *argv[]){

    int shm_fd, consumed = 0;
    char *shmpath;
    SharedBuffer *consBuff;

    if(argc != 2){
        fprintf(stderr, "Usage: %s /shm-path\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    shmpath = argv[1];

    shm_fd = shm_open(shmpath, O_RDWR, 0666);

    if(shm_fd == -1){
        err(EXIT_FAILURE, "shm_open");
    }

    
    consBuff = mmap(NULL, sizeof(SharedBuffer),
                    PROT_READ | PROT_WRITE,
                    MAP_SHARED, shm_fd, 0);

    if(consBuff == MAP_FAILED){
        err(EXIT_FAILURE, "mmap");
    }

    while(consumed < 20){
        
        /*Busy waiting enquanto o buffer estiver vazio*/
        while(consBuff->in == consBuff->out);

        uint16_t value = consBuff->buffer[consBuff->out];

        consBuff->out = (consBuff->out + 1) % BUFFER_SIZE;

        printf("Consumed: %u\n", value);
        consumed++;

        if (consumed < 20) {
        if (consumed % 4 == 0)
            sleep(10);
        else
            sleep(1);

        }
    }

    if (munmap(consBuff, sizeof(SharedBuffer)) == -1)
    err(EXIT_FAILURE, "munmap");

    if (close(shm_fd) == -1)
        err(EXIT_FAILURE, "close");

    if (shm_unlink(shmpath) == -1)
        err(EXIT_FAILURE, "shm_unlink");

    printf("Shared memory successfully removed.\n");
    
    return 0;
}




/*
https://www.youtube.com/watch?v=Pgq0xMqLWFM
*/


/*
o consumidor tem uma logica parecida ao produtor:
-verificar se está vazio
-se vazio, esperar
-retirar valor de indice out
-print valor retirado
-repetir até ao infinito e mais além
*/