#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void* myThreadFunction(void* arg){
    pthread_t current_threadId = pthread_self();
    printf("Thread : Thread %lu is created and running ... \n", (unsigned long)current_threadId);

    return NULL;
}

int main(){
    int n;
    printf("Enter the number of the thread : \n");
    scanf("%d",&n);
    pthread_t thread_array[n];

    
    printf("Main Thread : Creating %d threads ...\n" , n);

    for(int i=0;i<n;i++){
        int rc = pthread_create(&thread_array[i],NULL, myThreadFunction, NULL);
        if(rc){
            printf("There is an error creating the thread.\n");
            return 1;
        }
        printf("Main Thread : Thread with ID %lu is created.\n",(unsigned long)thread_array[i]);
    }
    
    
    for(int i=0;i<n;i++){
        pthread_join(thread_array[i] , NULL);
    }
    return 0;
}