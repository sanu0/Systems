// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>

// struct data{
//     int * arr;
//     int start;
//     int end;
// };

// void* myThreadFunction(void* arg){

//     struct data* dat = (struct data*)arg;
//     long long current_partial_sum = 0;
//     for(int i= dat->start ; i<dat->end ;i++){
//         current_partial_sum += dat->arr[i];
//     }

//     // Allocate memory on the heap for the return value
//     // This is CRUCIAL. You cannot return a pointer to a local stack variable.
//     long long *result_ptr = malloc(sizeof(long long));
//     if (result_ptr == NULL) {
//         perror("Thread: Failed to allocate memory for return value");
//         pthread_exit(NULL); // Exit thread gracefully if malloc fails
//     }
//     *result_ptr = current_partial_sum; // Store the partial sum in the allocated memory
//     printf("Thread Id : %ld (partial sum) = %lld \n", pthread_self(), *result_ptr);
//     pthread_exit((void *)result_ptr); // This is the correct way to return a value

// }

// int main(){

//     int n;
//     printf("Enter the number of the thread : \n");
//     scanf("%d",&n);
//     pthread_t thread_array[n];

//     int size = 100;
//     int *arr = (int *) malloc(size * sizeof(int));
//     for(int i=0;i<size;i++){
//         arr[i] = i+1;
//     }

//     for(int i=0;i<n;i++){
//         struct data dat;
//         int val = (size / n);
//         dat.arr = arr;
//         dat.start = val * i;
//         if(i == n-1){
//             dat.end = size;
//         }else{
//             dat.end = (i+1)*val;
//         }
//         int rc = pthread_create(&thread_array[i], NULL, myThreadFunction , (void *)&dat);

//         if(rc){
//             printf("Main thread : There is some error in the thread spawning! \n");
//             return 1;
//         }
//         //printf("Main Thread : Thread with ID %lu is created.\n",(unsigned long)thread_array[i]);
//     }

//     //This is how we handle the returned value from the pthreads

//     long long total_sum = 0;

//     void *partial_sum_ptr;

//     for(int i=0;i<n;i++){

//         int rc = pthread_join(thread_array[i] , &partial_sum_ptr);
//         if(rc){
//             printf("Main thread : Error occurs in joining the threads!");
//             return 2;
//         }
//         if(partial_sum_ptr != NULL){
//             long long partial_sum = *(long long *)partial_sum_ptr;
//             total_sum += partial_sum;
//             free(partial_sum_ptr);
//             partial_sum_ptr = NULL;
//         }else{
//             printf("Main Thread: Thread %d (ID: %lu) returned NULL (possible error in thread).\n", i, (unsigned long)thread_array[i]);
//         }
//     }
//     free(arr);
//     printf("Main Thread : Total Sum : %lld \n" , total_sum);
//     return 0;
// }



/**

The Root Cause of Incorrect/Inconsistent Sums:

1. Local Variable Lifetime: struct data dat; declares dat as a local variable on the main thread's stack. 
Every time the for loop iterates, this dat variable is created (or rather, its memory location is reused).

2. Race to the Pointer: When pthread_create is called, it takes the address of dat (&dat) and passes it to your myThreadFunction. 
However, pthread_create starts the thread but doesn't guarantee it runs immediately. The main thread continues iterating the loop.

3. Data Corruption: By the time a newly spawned thread actually gets scheduled and begins executing myThreadFunction, 
the main thread has likely already: Proceeded to the next iteration of the loop, overwriting the contents of dat with new start/end values 
for the next thread.Or, even finished the for loop entirely, making the dat's memory potentially invalid or reused for other purposes.

-----------------------------------------------------------------------------------------------------------------------------------------------
This means that your threads are likely reading the start and end values (and thus arr) that were set for a different thread, 
or even garbage values, leading to incorrect and non-deterministic sums.

The Solution: Allocate Thread Arguments on the Heap. You need a separate, persistent struct data for each thread. 
The safest way to do this is to allocate an array of these structs on the heap, outside the loop.

-----------------------------------------------------------------------------------------------------------------------------------------------

*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct data{
    int * arr;
    int start;
    int end;
};

void* myThreadFunction(void* arg){

    struct data* dat = (struct data*)arg;
    long long current_partial_sum = 0;
    for(int i= dat->start ; i<dat->end ;i++){
        current_partial_sum += dat->arr[i];
    }

    // Allocate memory on the heap for the return value
    // This is CRUCIAL. You cannot return a pointer to a local stack variable.
    long long *result_ptr = malloc(sizeof(long long));
    if (result_ptr == NULL) {
        perror("Thread: Failed to allocate memory for return value");
        pthread_exit(NULL); // Exit thread gracefully if malloc fails
    }
    *result_ptr = current_partial_sum; // Store the partial sum in the allocated memory
    printf("Thread Id : %ld (partial sum) = %lld \n", pthread_self(), *result_ptr);
    pthread_exit((void *)result_ptr); // This is the correct way to return a value

}

int main(){

    int n;
    printf("Enter the number of the thread : \n");
    scanf("%d",&n);
    pthread_t thread_array[n];

    int size = 100;
    int *arr = (int *) malloc(size * sizeof(int));
    for(int i=0;i<size;i++){
        arr[i] = i+1;
    }

    // FIX START: Dynamically allocate an array of struct data for thread arguments
    struct data *thread_args_array = (struct data *)malloc(n * sizeof(struct data));
    if (thread_args_array == NULL) {
        perror("Main thread: Failed to allocate memory for thread arguments");
        free(arr); // Clean up already allocated array
        return 1;
    }

    for(int i=0;i<n;i++){
        // FIX: Use the element from the dynamically allocated array
        // Each thread_args_array[i] is a separate, persistent struct.
        thread_args_array[i].arr = arr;
        int val = (size / n);
        thread_args_array[i].start = val * i;
        
        // Ensure the last thread covers any remaining elements
        if(i == n-1){
            thread_args_array[i].end = size;
        }else{
            thread_args_array[i].end = (i+1)*val;
        }

        int rc = pthread_create(&thread_array[i], NULL, myThreadFunction , (void *)&thread_args_array[i]);
        if(rc){
            printf("Main thread : There is some error in the thread spawning! \n");
            return 1;
        }
        //printf("Main Thread : Thread with ID %lu is created.\n",(unsigned long)thread_array[i]);
    }

    //This is how we handle the returned value from the pthreads

    long long total_sum = 0;

    void *partial_sum_ptr;

    for(int i=0;i<n;i++){

        int rc = pthread_join(thread_array[i] , &partial_sum_ptr);
        if(rc){
            printf("Main thread : Error occurs in joining the threads!");
            return 2;
        }
        if(partial_sum_ptr != NULL){
            long long partial_sum = *(long long *)partial_sum_ptr;
            total_sum += partial_sum;
            free(partial_sum_ptr);
            partial_sum_ptr = NULL;
        }else{
            printf("Main Thread: Thread %d (ID: %lu) returned NULL (possible error in thread).\n", i, (unsigned long)thread_array[i]);
        }
    }
    free(arr);
    printf("Main Thread : Total Sum : %lld \n" , total_sum);
    return 0;
}


/**
Your main error was this line in the loop:
struct data dat;

This creates a dat variable that lives only for one iteration of the loop. When you pass &dat to pthread_create, you are passing the address 
of this temporary variable. As the main loop continues, the content of dat changes for the next thread. 
Threads that were created earlier might then read corrupted start and end values from that rapidly changing dat location, leading to incorrect sums.

The Fix:

By allocating ThreadArgs *thread_args_array = (struct data *)malloc(n * sizeof(struct data)); you create n distinct struct data instances on the heap. 
When you then fill thread_args_array[i] and pass (void *)&thread_args_array[i] to pthread_create, each thread receives a pointer to its own, 
dedicated, persistent copy of the arguments. This eliminates the race condition on the input arguments and ensures each thread correctly processes 
its assigned segment.

*/