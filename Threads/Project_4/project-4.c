#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>



int sharedCounter = 0; //shared variable (critical section)

pthread_mutex_t counter_mutex;

void* myThreadFunction(void* arg){
    
     printf("Thread ID: %lu starting incrementing...\n", (unsigned long)pthread_self()); // FIX: Correct cast for pthread_self()
    for(int i=0;i<10000;i++){
        pthread_mutex_lock(&counter_mutex);
        sharedCounter++;
        pthread_mutex_unlock(&counter_mutex);
    }
    printf("Thread ID: %lu finished incrementing.\n", (unsigned long)pthread_self()); // FIX: Correct cast for pthread_self()
    return NULL;
}

int main(){

    int n;
    printf("Enter the total number of threads : \n");
    scanf("%d",&n);
    pthread_t *threadArray = (pthread_t *)malloc( n * sizeof(pthread_t));


    int rc_mutex_init = pthread_mutex_init(&counter_mutex, NULL);
    if (rc_mutex_init != 0) {
        fprintf(stderr, "Main Thread: Error initializing mutex: %d\n", rc_mutex_init);
        free(threadArray);
        return 1;
    }

    printf("Main thread : Spawning %d threads.\n", n);
 
    for(int i=0;i<n;i++){

        int rc = pthread_create(&threadArray[i] , NULL, myThreadFunction , NULL);
        if(rc){
            printf("Main Thread : Error in spawning thread.\n");
            free(threadArray); // Clean up
            return 1;
        }
        
    }


    for(int i=0;i<n;i++){
        int rc = pthread_join(threadArray[i] , NULL);
        if(rc){
            printf("Main Thread : Some issue in joining the thread.\n");
            return 2;
        }
        
    }
    
    // FIX: The final result is simply the value of shared_counter
    printf("Main Thread : Final shared_counter value is %d \n", sharedCounter);

    // Verify the sum
    long long expected_value = (long long)n * 10000;
    printf("Main Thread : Expected value: %lld\n", expected_value);

    if (sharedCounter == expected_value) {
        printf("Main Thread : RESULT: CORRECT (unlikely without sync!)\n");
    } else {
        printf("Main Thread : RESULT: INCORRECT (Race condition observed!)\n");
        printf("Main Thread : Difference: %lld\n", expected_value - sharedCounter);
    }



    free(threadArray);
    return 0;
}