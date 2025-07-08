#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int *shared_buffer;
int buffer_ptr = 0;

pthread_mutex_t buffer_mutex;

void *producer_thread_func(void* arg){
    while(buffer_ptr < 100){
        pthread_mutex_lock(&buffer_mutex);
        shared_buffer[buffer_ptr++] = buffer_ptr;
        printf("Producer Thread : Producer produces.\n");
        pthread_mutex_unlock(&buffer_mutex);
    }
    pthread_exit(NULL);
}

void *consumer_thread_func(void* arg){
    while(buffer_ptr > 0){
        pthread_mutex_lock(&buffer_mutex);
        shared_buffer[buffer_ptr--] = 0;
        printf("Consumer Thread : Consumer consumes.\n");
        pthread_mutex_unlock(&buffer_mutex);
    }
    pthread_exit(NULL);
}

int main(){

    pthread_t producer_thread;
    pthread_t consumer_thread;
    shared_buffer = (int *) malloc(100 * sizeof(int));
    
    int rc_mutex_init = pthread_mutex_init(&buffer_mutex, NULL);
    if(rc_mutex_init != 0){
        printf("Main Thread : There is an error in initializing the buffer mutex. \n");
        return 1;
    }

    printf("Main Thread : Creating producer and Consumer Thread. \n");

    int rc_producer = pthread_create(&producer_thread , NULL, producer_thread_func, NULL);
    if(rc_producer){
        printf("Main Thread : There is an error in creating producer thread. \n");
        return 2;
    }

    int rc_consumer = pthread_create(&consumer_thread , NULL, consumer_thread_func, NULL);
    if(rc_consumer){
        printf("Main Thread : There is an error in creating consumer thread. \n");
        return 2;
    }

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    free(shared_buffer);

    return 0;
}