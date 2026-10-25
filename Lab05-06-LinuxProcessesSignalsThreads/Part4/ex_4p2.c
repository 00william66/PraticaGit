#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t seconds = 0;
volatile sig_atomic_t suspended = 0; /*0- counting, 1- paused*/

void signalHandler(int sig);

int main(void)
{
    struct sigaction sa;

    sa.sa_handler = signalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGHUP, &sa, NULL);
    sigaction(SIGCONT, &sa, NULL);

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