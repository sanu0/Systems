#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>



int sharedCounter = 0; //shared variable (critical section)

void* myThreadFunction(void* arg){
    
    for(int i=0;i<100000;i++){
        sharedCounter++;
    }
    printf("Thread Id : %ld is running.\n" , pthread_self());
    return NULL;
}

int main(){

    int n;
    printf("Enter the total number of threads : \n");
    scanf("%d",&n);
    pthread_t *threadArray = (pthread_t *)malloc( n * sizeof(pthread_t));


    printf("Main thread : Spawning %d threads.\n", n);
 
    for(int i=0;i<n;i++){

        int rc = pthread_create(&threadArray[i] , NULL, myThreadFunction , (void *)&sharedCounter);
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
    long long expected_value = (long long)n * 100000;
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