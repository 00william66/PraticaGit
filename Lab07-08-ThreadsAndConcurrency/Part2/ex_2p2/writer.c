#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    
    int fd, *counter;
    char *shmpath;


    if(argc != 2){
        fprintf("Usage: %s /shm-path\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    shmpath = argv[1];

    fd = shm_open(shmpath, O_CREAT | O_EXCL | O_RDWR, 0600);
    if(fd == -1){
        err(EXIT_FAILURE, "shm_open");
    }

    if(ftruncate(fd, sizeof(int)) == -1){
        err(EXIT_FAILURE, "ftruncate");
    }

    counter = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

}



/*

-verificar se o argumento foi bem passado no terminal 
(if(argc!=2))

-criar memória -> shm_open

-verificação se a criação da memória falhou

-definir o tamanho da memoria ftruncate

-mapear a memória, neste caso escrever

-verificar se o mapeamento falhou

*/