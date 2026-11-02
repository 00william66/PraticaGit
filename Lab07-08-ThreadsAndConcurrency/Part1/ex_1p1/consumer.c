#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_PATH "/tmp/my_fifo"

int main(void){
    int fd;
    int number;

    /*Criar fifo caso ainda não exista*/
    mkfifo(FIFO_PATH, 0666); /*0666 permite leitura e escrita*/

    printf("Consumer: Waiting for producer to open fifo...\n");
    fd = open(FIFO_PATH, O_RDONLY);
    if(fd == -1){
        perror("Error openinf fifo to write\n");
        return 1;
    }

    printf("Consumer ready -> Waiting for data to print...\n");
    while(read(fd, &number, sizeof(int)) > 0){
        
        printf("Consumer received: %d\n", number);

    }
    close(fd);
    unlink(FIFO_PATH);
    printf("Terminating consumer...\n");
    return 0;
}


/*Como estava a executar o programa numa 
pasta partilhada do Windows dentro do WSL 
( /mnt/c/Users/...), o sistema de
 ficheiros do Windows não suporta a 
 criação de ficheiros especiais do Linux, como os Named Pipes (FIFOs).
 
 Solução->a pasta /tmpp do linux fica dentro do disco virtual do wwsl que 
 suporta fifos
 */



/*O valor de retorno do read() pode ser:
Maior que 0 (> 0): O número exato de bytes lidos (no caso, 4 bytes por cada inteiro)
Igual a 0 (== 0): Fim de Ficheiro (EOF) Em pipes, isto acontece quando o Produtor fecha a sua ponta do FIFO (close(fd))
Igual a -1 (-1): erro na leitura*/



/*a diferença entre usar perror e printf é que o 
perror imprime a mensagem seguida de ':' e a 
explicação do erro*/