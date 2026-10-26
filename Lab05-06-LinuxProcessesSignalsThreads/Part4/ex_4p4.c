#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


volatile sig_atomic_t counter = 0;
void signalHandler(int sig);

int main(void)
{
    
    pid_t pid = fork();

    if(pid < 0){
        printf("Fo(r)king error");
    } else if (pid == 0){
        /*filho*/
        struct sigaction sa;
        sa.sa_handler = signalHandler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGUSR1, &sa, NULL);

        printf("Child (PID: %d) ready.\n\n", getpid());
        fflush(stdout);
        
        while (counter < 10) {
            pause(); /* Suspende até chegar o sinal */
                     /* O sinal chega, o handler corre e faz contador++ */
                     /* O pause "desbloqueia" e o programa avança */
            
            printf("Child: Received SIGUSR1 signal (%d/10)\n\n", counter);
            fflush(stdout);
        }
        
        printf("Child: Received all 10 signals. Terminating...\n");
        exit(0);

    } else {
        int i;
        printf("Parent (PID: %d) sending to child (PID: %d)...\n", getpid(), pid);
        sleep(1); /*dar tempo ao filho de executar e bloquear no pause.
        estava a acontecer o que não era suposto. era enviado o primeiro sinal 
        antes de child estar pronto*/

        for(i = 1; i <= 10; i++){
            kill(pid, SIGUSR1);
            printf("Parent: Sent SIGUSR1 signal (%d/10)\n", i);
            fflush(stdout);
            sleep(1);
        }
        
        wait(NULL);
        printf("Child terminated. Terminating parent...\n");
    }
    return 0;
}


void signalHandler(int sig)
{
    if(sig == SIGUSR1){
        counter++;
    }
}