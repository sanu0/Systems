#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// int *shared_buffer;
// int buffer_ptr = 0;

// pthread_mutex_t buffer_mutex;

// void *producer_thread_func(void* arg){
//     while(buffer_ptr < 100){
//         pthread_mutex_lock(&buffer_mutex);
//         shared_buffer[buffer_ptr++] = buffer_ptr;
//         printf("Producer Thread : Producer produces.\n");
//         pthread_mutex_unlock(&buffer_mutex);
//     }
//     pthread_exit(NULL);
// }

// void *consumer_thread_func(void* arg){
//     while(buffer_ptr > 0){
//         pthread_mutex_lock(&buffer_mutex);
//         shared_buffer[buffer_ptr--] = 0;
//         printf("Consumer Thread : Consumer consumes.\n");
//         pthread_mutex_unlock(&buffer_mutex);
//     }
//     pthread_exit(NULL);
// }

// int main(){

//     pthread_t producer_thread;
//     pthread_t consumer_thread;
//     shared_buffer = (int *) malloc(100 * sizeof(int));
    
//     int rc_mutex_init = pthread_mutex_init(&buffer_mutex, NULL);
//     if(rc_mutex_init != 0){
//         printf("Main Thread : There is an error in initializing the buffer mutex. \n");
//         return 1;
//     }

//     printf("Main Thread : Creating producer and Consumer Thread. \n");

//     int rc_producer = pthread_create(&producer_thread , NULL, producer_thread_func, NULL);
//     if(rc_producer){
//         printf("Main Thread : There is an error in creating producer thread. \n");
//         return 2;
//     }

//     int rc_consumer = pthread_create(&consumer_thread , NULL, consumer_thread_func, NULL);
//     if(rc_consumer){
//         printf("Main Thread : There is an error in creating consumer thread. \n");
//         return 2;
//     }

//     pthread_join(producer_thread, NULL);
//     pthread_join(consumer_thread, NULL);

//     free(shared_buffer);

//     return 0;
// }

/**
Problem with the above is that even if the producer produces and completes the whole array even then the consumer consumption is not guarenteed to start.
Due to busy waiting it wastes many CPU cycles. Also the shared Resource (array) is not circular and buffer_ptr is acting as both pointer where to put
and how many items is there and there is no specific count variable to count the total number of items produced yet or total number of items there in the
array.  
*/


#define BUFFER_SIZE 10
#define NUM_OF_ITEM_TO_PRODUCE 200

int* shared_buffer;             //Shared Resource
int count = 0;                  //Count number of items in buffer
int in = 0;                     //points where producer can produce in shared resource
int out = 0;                    //points from where the consumer can consumes.

// Condition variable and mutex initialization
pthread_mutex_t buffer_mutex;
pthread_cond_t buffer_not_empty;
pthread_cond_t buffer_not_full;

void* producer_thread_func(void * arg){
    int item;
    for(int i=0;i<NUM_OF_ITEM_TO_PRODUCE;i++){
        item = i+1;

        pthread_mutex_lock(&buffer_mutex);
        while(count == BUFFER_SIZE){
            printf("Producer-Thread : Buffer is full! waiting for the consumer to consume.\n");
            pthread_cond_wait(&buffer_not_full,&buffer_mutex);
        }
        
        shared_buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        printf("Producer Thread : Producer produces %d-th item.\n",i+1);
        pthread_cond_signal(&buffer_not_empty); 
        pthread_mutex_unlock(&buffer_mutex);
        // Simulate variable production time
        //sleep(rand() % 2); // Sleep for 0 or 1 second
    }
    printf("Producer Thread: Finished producing all %d items.\n", NUM_OF_ITEM_TO_PRODUCE);
    pthread_exit(NULL);
}

void* consumer_thread_func(void * arg){
    int item;
    for(int i=0;i<NUM_OF_ITEM_TO_PRODUCE;i++){

        pthread_mutex_lock(&buffer_mutex);
        while(count == 0){
            printf("Consumer-Thread : Buffer is empty! waiting for the producer to produce.\n");
            pthread_cond_wait(&buffer_not_empty,&buffer_mutex);
        }
        
        
        item = shared_buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        printf("Consumer Thread : Consumer consumes %d-th item.\n",i+1);
        pthread_cond_signal(&buffer_not_full); 
        pthread_mutex_unlock(&buffer_mutex);
        // Simulate variable consumption time
        //sleep(rand() % 2); // Sleep for 0 or 1 second
    }
    printf("Consumer Thread: Finished Consuming all %d items.\n", NUM_OF_ITEM_TO_PRODUCE);
    pthread_exit(NULL);
}

int main(){

    pthread_t producer_thread, consumer_thread;
    shared_buffer = (int *)malloc(BUFFER_SIZE * sizeof(int));
    if (shared_buffer == NULL) {
        perror("Main: Failed to allocate shared buffer\n");
        return 1;
    }
    //initializing the mutex
    pthread_mutex_init(&buffer_mutex , NULL);
    pthread_cond_init(&buffer_not_empty, NULL);
    pthread_cond_init(&buffer_not_full, NULL);

    int rc_producer = pthread_create(&producer_thread,NULL,producer_thread_func,NULL);
    if(rc_producer){
        perror("Main Thread : There is an error in spawning producer-thread. \n");
        pthread_mutex_destroy(&buffer_mutex);
        pthread_cond_destroy(&buffer_not_empty);
        pthread_cond_destroy(&buffer_not_full);
        free(shared_buffer);
        return 2;
    }

    int rc_consumer = pthread_create(&consumer_thread,NULL,consumer_thread_func,NULL);
    if(rc_consumer){
        perror("Main Thread : There is an error in spawning consumer-thread. \n");
        pthread_mutex_destroy(&buffer_mutex);
        pthread_cond_destroy(&buffer_not_empty);
        pthread_cond_destroy(&buffer_not_full);
        free(shared_buffer);
        return 3;
    }

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread,NULL);

    printf("Main Thread: All items produced and consumed. Program finished.\n");

    pthread_mutex_destroy(&buffer_mutex);
    pthread_cond_destroy(&buffer_not_empty);
    pthread_cond_destroy(&buffer_not_full);
    free(shared_buffer);

    return 0;
}

