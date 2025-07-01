// #include <stdio.h>
// #include <pthread.h>   // Include the pthreads header
// #include <unistd.h>    // For sleep() (optional, just for demonstration)

// //Function that will be executed by the new thread.
// void *myThreadFunction(void *arg){
//     char *message = (char *)arg; //Cast the argument bacl to char*
//     printf("Hello from thread! Message : %s\n", message);
//     sleep(1); // Simulate some work
//     printf("Thread %s exiting. \n", message);
//     return NULL; //Threads usually return NULL or an int pointer.
// }


// int main(){
//     pthread_t thread_id; //Variable to store the thread ID
//     char *msg = "My awesome thread";

//     printf("Main thread : Creating a new thread ...\n");

//     // Create a new thread
//     // Arg 1: Pointer to pthread_t variable
//     // Arg 2: Thread attributes (NULL for default)
//     // Arg 3: Function to be executed by the thread
//     // Arg 4: Argument to pass to the thread function

//     int rc = pthread_create(&thread_id, NULL, myThreadFunction, (void *)msg );

//     if(rc){ //Check for Error
//         fprintf(stderr, "Error creating thread : %d \n", rc);
//         return 1;
//     }

//     printf("Main thread: Thread created with ID %lu\n", (unsigned long)thread_id);
//     // Wait for the created thread to finish
//     // Arg 1: Thread ID to wait for
//     // Arg 2: Pointer to store the return value of the thread (NULL if not needed)
//     pthread_join(thread_id, NULL);

//     printf("Main thread: Thread has finished. Exiting main.\n");

//     return 0;
// }

#include <stdio.h>    // Standard Input/Output library (for printf, fprintf, stderr)
#include <pthread.h>  // POSIX Threads library (for pthread_create, pthread_join, pthread_t)
#include <unistd.h>   // Unix Standard library (for sleep() - optional, just for demo)

// 1. Thread Function Definition
// This function will be executed by the new thread.
// It must have a 'void *' return type and accept a single 'void *' argument.
void *myThreadFunction(void *arg) {
    // 1a. Type casting the argument back to its original type (char*)
    char *message = (char *)arg; 

    // 1b. Print a message from the thread
    printf("Hello from thread! Message: %s\n", message);
    
    // 1c. Simulate some work or delay (optional)
    sleep(1); // Makes the thread pause for 1 second

    // 1d. Print another message indicating the thread is about to exit
    printf("Thread %s exiting.\n", message);
    
    // 1e. Threads typically return NULL or a pointer to an integer/data
    return NULL; 
}

// 2. Main Function (The "Main Thread")
// This is the entry point of your program, running as the initial thread.
int main() {
    // 2a. Declare a variable to hold the ID of the new thread
    pthread_t thread_id; 
    
    // 2b. Define a string message to pass to the new thread
    char *msg = "My awesome thread"; 

    // 2c. Print a message from the main thread
    printf("Main thread: Creating a new thread...\n");

    // 2d. Create the new thread
    // pthread_create() is the core function for spawning a new thread.
    // Arg 1: A pointer to the pthread_t variable where the new thread's ID will be stored.
    // Arg 2: Thread attributes (e.g., stack size, detached state). NULL means use default attributes.
    // Arg 3: A pointer to the function that the new thread will start executing (myThreadFunction in this case).
    // Arg 4: A pointer to an argument that will be passed to the thread function (myThreadFunction).
    //        We cast 'msg' (char*) to 'void *' because pthread_create expects a generic pointer.
    int rc = pthread_create(&thread_id, NULL, myThreadFunction, (void *)msg);

    // 2e. Error handling for thread creation
    if (rc) { // If rc is non-zero, an error occurred
        fprintf(stderr, "Error creating thread: %d\n", rc); // Print error to standard error
        return 1; // Exit with an error code
    }

    // 2f. Print the ID of the newly created thread
    // %lu is used for unsigned long, as pthread_t is often an unsigned long type.
    // We cast thread_id to unsigned long for printing.
    printf("Main thread: Thread created with ID %lu\n", (unsigned long)thread_id);

    // 2g. Wait for the new thread to finish its execution
    // pthread_join() makes the calling thread (main thread) wait until the specified thread terminates.
    // Arg 1: The ID of the thread to wait for (thread_id).
    // Arg 2: A pointer to a 'void *' where the return value of the joined thread will be stored.
    //        NULL means we don't care about the return value in this example.
    pthread_join(thread_id, NULL);

    // 2h. Print a message indicating the main thread is done waiting
    printf("Main thread: Thread has finished. Exiting main.\n");

    // 2i. Return 0 to indicate successful program execution
    return 0;
}