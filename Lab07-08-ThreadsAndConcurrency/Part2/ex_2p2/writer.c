#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <signal.h>
#include <err.h>



typedef struct{
    int counter;
    pid_t reader_pid;
} shm_data; /*no bloco de memoria partilhada queremos guardar
o counter como faziamos antes, mas também o pid do leitor
Assim o leitor pode escrever lá o seu pid, o escritor fica a conhecer
o seu pid e envia o sinal ao processo certo*/

volatile sig_atomic_t running = 1;

void handler(int sig);


int main(int argc, char *argv[]){
    
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    volatile shm_data *data;
    int fd;
    char *shmpath;

    if(argc != 2){
        fprintf(stderr, "Usage: %s /shm-path\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    shmpath = argv[1];

    fd = shm_open(shmpath, O_CREAT | O_EXCL | O_RDWR, 0666);
    if(fd == -1){
        err(EXIT_FAILURE, "shm_open");
    }

    if(ftruncate(fd, sizeof(shm_data)) == -1){
        err(EXIT_FAILURE, "ftruncate");
    }

    data = (volatile shm_data *)mmap(NULL, sizeof(shm_data), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    if(data == MAP_FAILED){
        err(EXIT_FAILURE, "mmap");
    }

    /*INICIALIZAR CONTADOR A 0*/
    data->counter = 0;
    data->reader_pid = 0;
    
    printf("Initializing writer... Press Ctrl+C to terminate.\n");

    while(running){
        data->counter++;
        if (data->reader_pid > 0) {
            kill(data->reader_pid, SIGUSR1);
        }
        printf("Writer: Updated time-> %ds\n", data->counter);
        fflush(stdout);
        sleep(1);
    }

    printf("Terminating writer...\n");

    munmap((void *)data, sizeof(shm_data)); /*void * para calar o compilador*/
    close(fd);
    shm_unlink(shmpath);
    return 0;
}



void handler(int sig){
    if(sig == SIGINT){
        running = 0;
    }
}