#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int sig);

int main(void)
{
    struct sigaction sa;

    sa.sa_handler = signalHandler;
    sigemptyset(&sa.sa_mask); /*Não bloquear sinais adicionais durante o handler*/
    sa.sa_flags = 0; /*default*/

    /*Registar os 4 sinais, sigaction(configura um sinal de cada vez)*/
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGHUP, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGCONT, &sa, NULL);

    printf("Program in execution (PID: %d). Waiting for signals...\n", getpid());

    while(1) {
        pause(); /*Suspende o processo ate chegar um sinal*/ 
    }

    return 0;

}

void signalHandler(int sig){
    switch(sig){
        case SIGINT:
        printf("\nReceived signal SIGINT\n");    
        break;

        case SIGHUP:
        printf("\nReceived signal SIGHUP\n"); 
        break;

        case SIGUSR1:
        printf("\nReceived signal SIGUSR1\n");
        break;

        default:
        printf("\nReceived an unhandled signal: %d\n", sig);
        break;
    }
    
}