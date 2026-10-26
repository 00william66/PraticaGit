#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <stdbool.h>

#define NEXECUTIONS 10

volatile int counter = 0;
volatile bool flag = 0; 

void *thread1(void *arg);
void *thread2(void *arg);

int main(void)
{
   

    pthread_t tid1, tid2;

    printf("Main thread: creating two threads named 1 and 2\n");

    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Threads 1 and 2 finished, terminating main thread...\n");
    return 0;
}

void *thread1(void *arg)
{
    
    while(counter <= NEXECUTIONS){
        sleep(1);
        counter++;
        flag = 1; /*sinalizar que houve mudança na variavel counter*/
    }
    pthread_exit(NULL);
}

void *thread2(void *arg)
{
    
    while(counter <= NEXECUTIONS){
        if(flag == 1){ /*se é 1 quer dizer que counter foi atualizado*/
            printf("Elapsed seconds: %d\n", counter);
            fflush(stdout);
            flag = 0; /*auto explicativo trivial*/
        } else {
            flag = 0;
        }
        usleep(1000); /*Para não sobrecarregar o CPU no polling*/
    }
    pthread_exit(NULL);
}