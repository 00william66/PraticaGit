#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <err.h>
#include <stdint.h>
#include<pthread.h>


#define BUFFER_SIZE 10

typedef struct{
    int in, out, stored;
    uint16_t array[BUFFER_SIZE];
}SharedBuffer;

volatile SharedBuffer buffer;

sem_t sem;
pthread_mutex_t mutex;

void *workerProd(void *arg);
void *workerCons(void *arg);

int main(void){

    int rc;
    pthread_t producer, consumer;

    buffer.stored = 0;
    buffer.in = 0;
    buffer.out = 0;

    if(sem_init(&sem, 0, 0) == -1){
        err(EXIT_FAILURE, "sem_init");
    }

    rc = pthread_create(&producer, NULL, workerProd, NULL);
    if(rc != 0){
        err(EXIT_FAILURE, "pthread_create -> producer");
    }

    rc = pthread_create(&consumer, NULL, workerCons, NULL);
    if(rc != 0){
        err(EXIT_FAILURE, "pthread_create -> consumer");
    }


    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    sem_destroy(&sem);
    pthread_mutex_destroy(&mutex);

    return 0;
}


void *workerProd(void *arg){
    int produced = 0;
    while(produced < 20){
        while(buffer.stored == BUFFER_SIZE) /*busy waiting enquanto o buffer está cheio*/
        usleep(1000);

        buffer.array[buffer.in] = produced + 1;
        pthread_mutex_lock(&mutex);
        buffer.stored++;
        pthread_mutex_unlock(&mutex);

        buffer.in = (buffer.in + 1) % BUFFER_SIZE;

        produced++;
        printf("Produced: %d\n", produced);
        sem_post(&sem);
    }
    pthread_exit(NULL);
}


void *workerCons(void *arg){
    int consumed = 0;
    uint16_t value;

    while (consumed < 20){
        sem_wait(&sem);        
        value = buffer.array[buffer.out];
        buffer.out = (buffer.out + 1) % BUFFER_SIZE;
        pthread_mutex_lock(&mutex);
        buffer.stored--;
        pthread_mutex_unlock(&mutex);
        consumed++;

        printf("\t\t\tConsumed: %d\n", value);
        sleep(1);
    }
    pthread_exit(NULL);
}