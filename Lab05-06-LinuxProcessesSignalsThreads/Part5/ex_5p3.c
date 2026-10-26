#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <stdbool.h>

void signalHandler(int sig);
void *thread1(void *arg);
void *thread2(void *arg);
/*este programa deve criar duas threads e esperar pela receção de um sinal*/
int main(void)
{
    struct sigaction sa;
    sa.sa_handler = signalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    pthread_t tid1, tid2;

    printf("Main thread: creating two threads (thread1 and thread2)\n");

    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);

    pthread_kill(tid1, SIGUSR1);
    sleep(1);
    pthread_kill(tid2, SIGUSR1);    

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Terminated thread 1 and 2, terminating main.\n");

    return 0;
}

void signalHandler(int sig)
{
    (void)sig; /*evita avisos de argumento não utilizado*/
}

void *thread1(void *arg)
{
    (void)arg;
    pause(); /*ao receber o sinal, pause() é interrompido e é chamado o handler. O print 
    deve ser feito depois do pause, quando o handler terminar 
    e o fluxo de execução continuar na instrução a seguir ao pause*/
    printf("Thread 1: Received SIGUSR1\n");

    pthread_exit(NULL);
}


void *thread2(void *arg)
{
    (void)arg;
    pause();
    printf("Thread 2: Received SIGUSR1\n");

    pthread_exit(NULL);
}