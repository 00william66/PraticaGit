
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <err.h>
#include <sys/mman.h>
#include <signal.h>

#define BUFFER_SIZE 10

typedef struct{
    uint16_t buffer[BUFFER_SIZE];
    unsigned int in;
    unsigned int out;
    pid_t pid;
} SharedBuffer;

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

    prodBuff = mmap(NULL, sizeof(SharedBuffer),
                    PROT_READ | PROT_WRITE,
                    MAP_SHARED, shm_fd, 0);

    if(prodBuff == MAP_FAILED){
        err(EXIT_FAILURE, "mmap");
    }

    prodBuff->pid = 0;
    prodBuff->in = 0;
    prodBuff->out = 0;

    while (produced < 20) {

        /* Verificar se o buffer está cheio */
        while ((prodBuff->in + 1) % BUFFER_SIZE == prodBuff->out);

        /* Inserir elemento */
        uint16_t value = produced + 1;

        prodBuff->buffer[prodBuff->in] = value;

        /* Avançar índice in */
        prodBuff->in = (prodBuff->in + 1) % BUFFER_SIZE;

        /* Sinalizar consumidor */
        if(prodBuff->pid > 0){
            kill(prodBuff->pid, SIGUSR1);
        }

        printf("Produced: %u\n", (unsigned int)value);

        produced++;
    }

    munmap(prodBuff, sizeof(SharedBuffer));
    close(shm_fd);

    return 0;
}


/*até aqui ok, no consumidor estava a dar problemas
usar o pause porque havia uma race condition entre 
verificar o buffer e esperar pelo sinal.

reparar que o produtor está bloqueado sempre que o buffer está cheio
como é suposto
*/