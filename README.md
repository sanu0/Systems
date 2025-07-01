POSIX Threads (pthreads) Learning Projects
This repository contains a series of progressively challenging projects designed to help you master multithreading concepts using the POSIX Threads (pthreads) API in a C environment. Each project introduces a new core concept, building towards a comprehensive capstone project.

Environment: WSL2 Ubuntu
Language: C (using pthreads API)
Compilation: gcc -o <executable_name> <source_file>.c -pthread

The Threading Mastery Journey: 10 Core Projects + 1 Capstone
Project 1: The First Thread - "Hello, Concurrency!"
New Concept: Basic Thread Creation & Joining

Description: Spawn multiple threads, each printing a unique message. The main thread waits for all threads to complete.

Learning Focus: pthread_create(), pthread_join(), observing non-deterministic execution.

Hardness Level: 1/10

Project 2: Passing & Receiving Data - Parallel Sum
New Concept: Passing Arguments to Threads & Retrieving Return Values

Description: Divide a large array summation among multiple threads. Each thread calculates a partial sum and returns it to the main thread for a final total.

Learning Focus: Passing structs to threads, returning void* results via pthread_join().

Hardness Level: 2/10

Project 3: The Broken Counter - Observing Race Conditions
New Concept: Identifying and Experiencing Race Conditions

Description: Multiple threads concurrently increment a shared global counter. Observe that the final count is incorrect due to race conditions.

Learning Focus: Direct experience of shared mutable state issues without synchronization.

Hardness Level: 3/10

Project 4: The Protected Counter - Mutual Exclusion with Mutexes
New Concept: Mutual Exclusion using Mutexes (pthread_mutex_t)

Description: Enhance Project 3 by using a mutex to protect the shared counter, ensuring correct final value.

Learning Focus: pthread_mutex_lock(), pthread_mutex_unlock(), solving simple race conditions.

Hardness Level: 4/10

Project 5: Producer-Consumer with a Bounded Buffer
New Concept: Inter-Thread Communication & Signaling using Condition Variables (pthread_cond_t)

Description: Implement a producer thread adding items to a fixed-size buffer and a consumer thread taking items. Use mutexes and condition variables to manage buffer fullness/emptiness.

Learning Focus: pthread_cond_wait(), pthread_cond_signal(), pthread_cond_broadcast(), mastering a crucial inter-thread communication pattern.

Hardness Level: 5/10

Project 6: Concurrent Access with Readers and Writers
New Concept: Reader-Writer Locks (pthread_rwlock_t)

Description: Implement a shared resource accessed by multiple reader and writer threads. Allow concurrent reads but exclusive writes using pthread_rwlock_t.

Learning Focus: pthread_rwlock_rdlock(), pthread_rwlock_wrlock(), optimizing access patterns.

Hardness Level: 6/10

Project 7: Dining Philosophers - Deadlock Prevention
New Concept: Deadlock Conditions & Prevention Strategies

Description: Solve the classic Dining Philosophers problem (5 philosophers, 5 forks) by implementing a deadlock prevention strategy (e.g., ordered resource acquisition).

Learning Focus: Deep understanding of deadlock, applying prevention techniques.

Hardness Level: 7/10

Project 8: Basic Thread Pool for Background Tasks
New Concept: Thread Pool Architecture & Task Queue Management

Description: Create a fixed-size pool of worker threads. Implement a shared task queue where the main thread submits tasks, and workers pick them up for execution.

Learning Focus: Efficient thread management, combining mutexes and condition variables for queue.

Hardness Level: 8/10

Project 9: Graceful Thread Termination - Cancellation & Detaching
New Concept: Controlled Thread Termination & Lifecycle Management

Description: Demonstrate pthread_cancel() for controlled thread termination (with cleanup handlers) and pthread_detach() for automatic resource reclamation.

Learning Focus: pthread_cancel(), pthread_detach(), pthread_cleanup_push/pop, managing thread lifecycle.

Hardness Level: 9/10

Project 10: Thread-Specific Data (TLS)
New Concept: Thread-Local Storage (TLS)

Description: Create multiple threads executing the same function, but each thread maintains its own independent copy of a variable using pthread_key_t.

Learning Focus: pthread_key_create(), pthread_setspecific(), pthread_getspecific(), isolating per-thread data.

Hardness Level: 9/10

Project 11: Capstone - Concurrent Web Log Analyzer
Integrates Concepts: Thread Pool, Producer-Consumer, Mutexes, Condition Variables, Data Passing, Error Handling, Graceful Shutdown, (Optional: Reader-Writer for results).

Description: Build a multi-threaded application to process a simulated web server log file.

Log File Simulation: Create a large text file with simulated web server log entries.

Input Thread (Producer): Reads lines from the log file, parses them, and places parsed log entries (as structs) into a bounded buffer (queue).

Worker Thread Pool (Consumers): A configurable number of worker threads pull parsed log entries from the buffer.

Log Analysis: Each worker thread analyzes its log entry, updating shared, mutex-protected data structures for aggregated statistics (e.g., total requests, counts by IP, counts by status code).

Graceful Shutdown: Implement mechanisms for the input thread to signal end-of-file, and for worker threads to process remaining items in the queue and then terminate gracefully. The main thread waits for all threads to finish.

Final Report: After all processing, the main thread prints a summary report of the aggregated statistics.

This capstone project will challenge you to combine and apply the various threading concepts learned throughout the previous 10 projects into a functional, robust, and concurrent application.