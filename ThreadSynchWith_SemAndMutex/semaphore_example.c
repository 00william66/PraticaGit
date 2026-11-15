#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;

void *worker(void *arg)
{
    printf("Worker: Waiting for permission...\n");

    sem_wait(&semaphore); /*Tira 1 ao valor do semaforo. 
    Se for 0 fica bloqueado até lhe ser dada permissão*/

    printf("Worker: Permission received! Continuing...\n");

    return NULL;
}

int main()
{
    pthread_t thread;

    // Inicializa semaforo com 0
    sem_init(&semaphore, 0, 0);

    pthread_create(&thread, NULL, worker, NULL);

    printf("Main: Doing some work...\n");
    sleep(5);
    // Deixa o worker work
    sem_post(&semaphore); /*Incrementa 1 ao valor do semaforo, 
    podendo acordar uma thread que esteja a espera.*/

    pthread_join(thread, NULL);

    sem_destroy(&semaphore);

    return 0;
}