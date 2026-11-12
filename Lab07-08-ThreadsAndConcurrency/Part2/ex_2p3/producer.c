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

    int shm_fd, produced = 0;
    char *shmpath;
    SharedBuffer *prodBuff;

    if(argc != 2){
        fprintf(stderr, "Usage: %s /shm-path\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    shmpath = argv[1];

    shm_fd = shm_open(shmpath, O_CREAT | O_EXCL | O_RDWR, 0666);

    if(shm_fd == -1){
        err(EXIT_FAILURE, "shm_open");
    }

    if(ftruncate(shm_fd, sizeof(SharedBuffer)) == -1){
        err(EXIT_FAILURE, "ftruncate");
    }

    /*
    map
    check if success
    */

    prodBuff = mmap(NULL, sizeof(SharedBuffer),
                    PROT_READ | PROT_WRITE, 
                    MAP_SHARED, shm_fd, 0);

    if(prodBuff == MAP_FAILED){
        err(EXIT_FAILURE, "mmap");
    }

    prodBuff->in = 0;
    prodBuff->out = 0; /*é importante que o produtor inicialize estas
                        variaveis antes de o consumidor começar a usá-las*/

    while (produced < 20) {

        /* Verificar se o buffer está cheio */
        while ((prodBuff->in + 1) % BUFFER_SIZE == prodBuff->out);

        /* Inserir elemento */
        uint16_t value = produced + 1;

        prodBuff->buffer[prodBuff->in] = value;

        /* Avançar índice in */
        prodBuff->in = (prodBuff->in + 1) % BUFFER_SIZE;

        /* Imprimir elemento inserido */
        printf("Produced: %u\n", (unsigned int)value);

        produced++;
    }

    munmap(prodBuff, sizeof(SharedBuffer));
    close(shm_fd);

    return 0;
}


/*
vamos ter varias coisas partilhadas pelos dois processos:
-array de 10 elementos
-indice in
-indice out

Produtor:
-Verifica se o buffer está cheio (in)
-Se cheio, esperar até haver espaço, pois que remédio
-Escrever nº em in
-Print nº
-Repetir até inserir os 20 nºs

tanto o produtor como o consumidor vão ter de poder ler e escrever na shared memory

*/