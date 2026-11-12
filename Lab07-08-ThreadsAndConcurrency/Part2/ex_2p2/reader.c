#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/mman.h>
#include <err.h>

typedef struct{
    int counter;
    pid_t pid;
}shm_data;

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
    sigaction(SIGUSR1, &sa, NULL);

    int fd;
    char *shmpath;
    volatile shm_data *data;

    if(argc != 2){
        fprintf(stderr, "Usage: %s /shm-path\n", argv[0]); /*argv[0] é o nome do programa, claro*/
        exit(EXIT_FAILURE); /*isto está na página, man*/
    }

    shmpath = argv[1];

    /*Criar objeto shared memory e truncar o seu tamanho para
    o tamanho de um inteiro, que é o tipo de counter*/

    fd = shm_open(shmpath, O_RDWR, 0666); /*o leitor precisa de escrever o seu pid*/
    if(fd == -1) {
        err(EXIT_FAILURE, "shm_open");
    }
    

    /*Mapear o objeto para o espaço de endereçamento do chamador*/
    data = (volatile shm_data *)mmap(NULL, sizeof(shm_data), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(data == MAP_FAILED){
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    
    data->pid = getpid();

    printf("Reader initializing... Press Ctrl+C to terminate\n");
    
    while(running){
        pause(); /*fica a espera do SIGUSR1*/
        if (running) {
            printf("Reader: Updated Elapsed time-> %ds\n", data->counter);
            fflush(stdout);
        }
        
    }

    printf("Terminating reader...\n");

    munmap((void *)data, sizeof(shm_data));
    close(fd);
    return 0;
}









void handler(int sig){
    if(sig == SIGINT){
        running = 0;
    }
}