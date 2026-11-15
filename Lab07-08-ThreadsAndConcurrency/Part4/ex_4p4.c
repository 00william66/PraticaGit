#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define NUM_INCREMENTS 1000000

int counter = 0;
pthread_mutex_t mutex;

void* increment(void* arg);

int main(void) {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Final counter value (with mutex): %d\n", counter);
    
    
    return 0;
}


void* increment(void* arg) {
	(void) arg;
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}  



/*
ESTRUTURA MUTEX:

#include <pthread.h>
pthread_mutex_t mutex;
----create and initialize mutex lock
pthread_mutex_init(&mutex, NULL);

----acquire the mutex lock
pthread_mutex_lock(&mutex);
---critical section

----release the mutex lock
pthread_mutex_unlock(&mutex);

*/