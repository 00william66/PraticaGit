#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

void *thread1(void *arg);
void *thread2(void *arg);

int main(void)
{

    pthread_t tid1, tid2;

    printf("Main thread: creating two threads named 1 and 2\n");

    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);

    pthread_join(tid1, NULL);
    printf("Thread 1 finishing\n");
    pthread_join(tid2, NULL);
    printf("Thread 2 finishing\n");

    printf("Main thread: both threads finished, exiting\n");

    return 0;
}

void *thread1(void *arg)
{
    printf("Thread 1 starting\n");
    pthread_exit(NULL);
}


void *thread2(void *arg)
{
    printf("Thread 2 starting\n");
    pthread_exit(NULL);
}