
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

void handler(int sig);

int main(int argc, char *argv[]){

    int shm_fd, consumed = 0;
    char *shmpath;
    SharedBuffer *consBuff;

    struct sigaction sa;
    sigset_t block_set, old_set, wait_set;

    /* Configurar handler */
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if(sigaction(SIGUSR1, &sa, NULL) == -1){
        err(EXIT_FAILURE, "sigaction");
    }

    /* Bloquear SIGUSR1 */
    sigemptyset(&block_set);
    sigaddset(&block_set, SIGUSR1);

    if(sigprocmask(SIG_BLOCK, &block_set, &old_set) == -1){
        err(EXIT_FAILURE, "sigprocmask");
    }

    wait_set = old_set;
    sigdelset(&wait_set, SIGUSR1);

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

    /* Registar PID do consumidor */
    consBuff->pid = getpid();

    while(consumed < 20){

        /* Esperar enquanto o buffer estiver vazio */
        while(consBuff->in == consBuff->out){
            sigsuspend(&wait_set);
        }

        /* Ler elemento */
        uint16_t value = consBuff->buffer[consBuff->out];

        /* Avançar índice out */
        consBuff->out = (consBuff->out + 1) % BUFFER_SIZE;

        printf("Consumed: %u\n", (unsigned int)value);

        consumed++;

        /* Simular processamento */
        if (consumed < 20) {
            if (consumed % 4 == 0){
                sleep(10);
            } else {
                sleep(1);
            }
        }
    }

    /* Restaurar máscara original */
    if(sigprocmask(SIG_SETMASK, &old_set, NULL) == -1){
        err(EXIT_FAILURE, "sigprocmask");
    }

    if(munmap(consBuff, sizeof(SharedBuffer)) == -1)
        err(EXIT_FAILURE, "munmap");

    if(close(shm_fd) == -1)
        err(EXIT_FAILURE, "close");

    if(shm_unlink(shmpath) == -1)
        err(EXIT_FAILURE, "shm_unlink");

    printf("Shared memory successfully removed.\n");

    return 0;
}

void handler(int sig){}

/*aqui é que foi a mudança 

a estrutura é a mesma do 2.3 mas o chat disse para usar o
sigprocmask e sigsuspend

confesso que não percebi muito bem mas como nem sequer estão
nas funções do formulario do sor não me vou chatear muito com isso
*/