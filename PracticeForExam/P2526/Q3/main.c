#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <err.h>

volatile long int global_sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *worker1(void *arg);
void *worker2(void *arg);

int main(void){
    
    long int n1 = 5, n2 = 10;

    pthread_t Thread_1, Thread_2;

    int rc;
    rc = pthread_create(&Thread_1, NULL, worker1, (void *)n1);
    if(rc != 0){
        err(EXIT_FAILURE, "pthread_create");
    }

    rc = pthread_create(&Thread_2, NULL, worker2, (void *)n2);
    if(rc != 0){
        err(EXIT_FAILURE, "pthread_create");
    }


    pthread_join(Thread_1, NULL);
    pthread_join(Thread_2, NULL);


    printf("Expected global sum: %ld\n", n1 + n2);
    printf("Global sum: %ld\n", global_sum);
    pthread_mutex_destroy(&mutex);

    return 0;
}


void *worker1(void *arg){
long int i;
    for(i = 0; i < (long int)arg; i++){
        pthread_mutex_lock(&mutex);
        global_sum++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}


void *worker2(void *arg){
long int i;
    for(i = 0; i < (long int)arg; i++){
        pthread_mutex_lock(&mutex);
        global_sum++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}


