Project 1: The First Thread - "Hello, Concurrency!"
New Concept: Basic Thread Creation & Joining

Description: Create a program where the main function (the main thread) spawns 3-5 new threads. Each new thread should simply print a message like "Hello from Thread [Thread ID]!" and then exit. The main thread must wait for all these newly created threads to complete their execution before the main program itself exits.

Learning Focus: Getting comfortable with pthread_create() to start threads and pthread_join() to synchronize their termination with the main thread. Observe the non-deterministic order of output messages.

Hardness Level: 1/10 (Fundamental)