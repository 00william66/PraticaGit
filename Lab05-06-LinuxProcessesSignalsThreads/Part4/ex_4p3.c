#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t seconds = 0;
volatile sig_atomic_t suspended = 0; /*0- counting, 1- paused*/

void signalHandler(int sig);

int main(void)
{
    int i;
    struct sigaction sa;
    struct sigaction sa_ignore;

    sa.sa_handler = signalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGHUP, &sa, NULL);
    sigaction(SIGCONT, &sa, NULL);

    /* Configurar a estrutura para ignorar outros sinais */
    sa_ignore.sa_handler = SIG_IGN; /*Atribuit SIG_IGN ao campo sa_handler
    indica ao SO que a ação para os sinais configurados com essa estrutura
    passa a ser IGNORAR O SINAL --> este comportamento só é aplicado
    no for com o sigaction ---man sigaction*/
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;

    for (i = 1; i < NSIG; i++) {
        if (i != SIGINT && i != SIGHUP && i != SIGCONT && i != SIGKILL && i != SIGSTOP) {
            sigaction(i, &sa_ignore, NULL);
        }
    }

    printf("Timer started (PID: %d)", getpid());

    while(1){
        if(!suspended){
            printf("Elapsed time: %d s\n", seconds);
            fflush(stdout);
            seconds++;
        }
        sleep(1);
    }

}



void signalHandler(int sig){
    switch(sig){
        case SIGINT:
        seconds = 0;
        suspended = 0;   
        break;

        case SIGHUP:
        suspended = 1; 
        break;

        case SIGCONT:
        suspended = 0;
        break;
        
    }
    
}