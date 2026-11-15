#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <err.h>

volatile int counter = 0; /*shared variable (global->vista por todas as threads)*/

void *increment_thread(void *arg);
void *print_thread(void *arg);


int main(void){

    pthread_t t_inc, t_print;
    int rc;
    
    rc = pthread_create(&t_inc, NULL, increment_thread, NULL);
    if(rc != 0){
        err(EXIT_FAILURE, "pthread_create -> increment");
    }

    /*rc só tem o valor de return de pthread_create.
    usa-se diretamente para saber se houve erro na criação da 
    thread e depois já não é preciso*/
    rc = pthread_create(&t_print, NULL, print_thread, NULL);
    if(rc != 0){
        err(EXIT_FAILURE, "pthread_create -> increment");
    }


    pthread_join(t_inc, NULL);
    pthread_join(t_print, NULL);

    return 0;
}


/*
* Thread 1 - incrementa o contador uma vez por segundo
*/

void *increment_thread(void *arg){

    while(1){
        sleep(1);
        counter++;
    }
    pthread_exit(NULL);
}

void *print_thread(void *arg){

    int last = counter; /*ultimo valor*/

    while(1){
        if(counter != last){
            last = counter;
            printf("Counter = %d\n", last);
        }
        usleep(1000);
    }
    pthread_exit(NULL);
}