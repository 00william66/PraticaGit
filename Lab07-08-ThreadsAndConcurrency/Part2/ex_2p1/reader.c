#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/mman.h>
#include <err.h>

volatile sig_atomic_t running = 1;

/*HANDLER PARA O SIGINT*/
void handler(int sig);


int main(int argc, char *argv[])
{

    /*CONFIG SIGINT*/
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);


    int fd, last_read_value = -1;
    char *shmpath;
    int *counter;

    if(argc != 2){
        fprintf(stderr, "Usage: %s /shm-path\n", argv[0]); /*argv[0] é o nome do programa, claro*/
        exit(EXIT_FAILURE); /*isto está na página, man*/
    }

    shmpath = argv[1];

    /*Criar objeto shared memory e truncar o seu tamanho para
    o tamanho de um inteiro, que é o tipo de counter*/

    fd = shm_open(shmpath, O_RDONLY, 0600);
    if(fd == -1) {
        err(EXIT_FAILURE, "shm_open");
    }
    

    /*Mapear o objeto para o espaço de endereçamento do chamador*/
    counter = (int *)mmap(NULL, sizeof(int), PROT_READ, MAP_SHARED, fd, 0);

    if(counter == MAP_FAILED){
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    printf("Reader initializing... Press Ctrl+C to terminate\n");
    
    while(running){
        if(*counter != last_read_value){
            printf("Reader: Updated Elapsed time-> %ds\n", *counter);
            fflush(stdout);
            last_read_value = *counter;
        }
    }

    printf("Terminating reader...\n");

    munmap((void *)counter, sizeof(int));
    close(fd);
    return 0;
}









void handler(int sig){
    if(sig == SIGINT){
        running = 0;
    }
}