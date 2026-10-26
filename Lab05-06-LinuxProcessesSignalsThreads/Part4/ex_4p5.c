#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

volatile sig_atomic_t counter = 0;
void signalHandler(int sig);

int main(void)
{
    /*Neste exercicio tenho de ter uma config
    diferentes --> os dois sinais exigem regras de 
    bloqueio diferentes
    
    SIGUSR1 - A máscara precisa de incluir o SIGUSR2 (usando sigaddset) 
    para garantir que este é bloqueado temporariamente enquanto o handler
    do SIGUSR1 está a ser executado.

    SIGUSR2 - A máscara fica limpa (vazia) pois é suposto
    manter o comportamento normal do sinal

    NOTA NO FINAL

    */
    struct sigaction sa;
    struct sigaction sa2;

    /*Configurar SIGUSR1*/
    sa.sa_handler = signalHandler;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR2);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    /*Configurar SIGUSR2*/
    sa2.sa_handler = signalHandler;
    sigemptyset(&sa2.sa_mask);
    sa2.sa_flags = 0;
    sigaction(SIGUSR2, &sa2, NULL);

    printf("Executing (PID: %d). Waiting for signals...\n", getpid());

    while(1){
        pause();
    }
}


void signalHandler(int sig)
{
    if(sig == SIGUSR1){
        counter++;
        printf("Received SIGUSR1. counter = %d\n", counter);
        fflush(stdout);

        sleep(15); /*para dar tempo de testar o bloqueio de SIGUSR2*/

        printf("Finished processing SIGUSR1\n");
        fflush(stdout);

    } else if(sig == SIGUSR2){
        printf("Received SIGUSR2 and executed it\n");
        fflush(stdout);

    }
}

/*EXECUTAR O PROGRAMA:

./ex_4p5 & --> executa o programa no background de modo a conseguir
enviar os sinais SIGUSR1 e SIGUSR2 no mesmo terminal

*/