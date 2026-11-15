#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <err.h>
#include <semaphore.h>

volatile int counter = 0; /*shared variable (global->vista por todas as threads)*/
sem_t sem;

void *increment_thread(void *arg);
void *print_thread(void *arg);


int main(void){

    pthread_t t_inc, t_print;
    int rc;
    
    if(sem_init(&sem, 0, 0) == -1){
        err(EXIT_FAILURE, "sem_init");
    }

    rc = pthread_create(&t_inc, NULL, increment_thread, NULL);
    if(rc != 0){
        err(EXIT_FAILURE, "pthread_create -> increment");
    }

    /*rc só tem o valor de return de pthread_create.
    usa-se diretamente para saber se houve erro na criação da 
    thread e depois já não é preciso*/
    rc = pthread_create(&t_print, NULL, print_thread, NULL);
    if(rc != 0){
        err(EXIT_FAILURE, "pthread_create -> print");
    }


    pthread_join(t_inc, NULL);
    pthread_join(t_print, NULL);

    sem_destroy(&sem);
    return 0;
}


/*
* Thread 1 - incrementa o contador uma vez por segundo
*/

void *increment_thread(void *arg){

    while(1){
        sleep(1);
        counter++;
        sem_post(&sem);
    }
    pthread_exit(NULL);
}

void *print_thread(void *arg){


    while(1){
        sem_wait(&sem);
        printf("Counter = %d\n", counter);
    }
    pthread_exit(NULL);
}