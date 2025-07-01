# POSIX Threads (pthreads) Learning Projects

This repository contains a series of progressively challenging projects designed to help you master multithreading concepts using the **POSIX Threads (pthreads)** API in a **C environment**. Each project introduces a new core concept, culminating in a comprehensive **Capstone Project**.

---

## 🛠 Environment

- **OS**: WSL2 Ubuntu  
- **Language**: C (with pthreads API)  
- **Compilation Command**:  
  ```bash
  gcc -o <executable_name> <source_file>.c -pthread


## 🚀 Threading Mastery Journey  
**10 Core Projects + 1 Capstone Project**

---

### 📘 Project 1: The First Thread - *"Hello, Concurrency!"*
- **New Concept**: Basic Thread Creation & Joining  
- **Description**: Spawn multiple threads, each printing a unique message. The main thread waits for all to complete.  
- **Learning Focus**: `pthread_create()`, `pthread_join()`, observing non-deterministic execution.  
- **Hardness Level**: 🔹 1/10  

---

### 📘 Project 2: Passing & Receiving Data - *Parallel Sum*
- **New Concept**: Passing Arguments & Retrieving Return Values  
- **Description**: Divide a large array among threads, compute partial sums, then aggregate.  
- **Learning Focus**: Passing structs, returning `void*` via `pthread_join()`.  
- **Hardness Level**: 🔹 2/10  

---

### 📘 Project 3: The Broken Counter - *Race Conditions*
- **New Concept**: Observing Race Conditions  
- **Description**: Threads increment a shared global counter without synchronization.  
- **Learning Focus**: Issues with shared mutable state.  
- **Hardness Level**: 🔹 3/10  

---

### 📘 Project 4: The Protected Counter - *Using Mutexes*
- **New Concept**: Mutual Exclusion with `pthread_mutex_t`  
- **Description**: Fix Project 3 using a mutex for synchronization.  
- **Learning Focus**: `pthread_mutex_lock()`, `pthread_mutex_unlock()`.  
- **Hardness Level**: 🔹 4/10  

---

### 📘 Project 5: Producer-Consumer with a Bounded Buffer
- **New Concept**: Condition Variables (`pthread_cond_t`)  
- **Description**: A producer adds items, and a consumer removes them, using a fixed-size buffer.  
- **Learning Focus**: `pthread_cond_wait()`, `pthread_cond_signal()`, buffer synchronization.  
- **Hardness Level**: 🔹 5/10  

---

### 📘 Project 6: Concurrent Access with Readers and Writers
- **New Concept**: Reader-Writer Locks (`pthread_rwlock_t`)  
- **Description**: Multiple readers and writers access a shared resource.  
- **Learning Focus**: `pthread_rwlock_rdlock()`, `pthread_rwlock_wrlock()` for access optimization.  
- **Hardness Level**: 🔹 6/10  

---

### 📘 Project 7: Dining Philosophers - *Deadlock Prevention*
- **New Concept**: Deadlocks & Avoidance Strategies  
- **Description**: Solve the Dining Philosophers problem using ordered resource acquisition.  
- **Learning Focus**: Understanding and preventing deadlocks.  
- **Hardness Level**: 🔹 7/10  

---

### 📘 Project 8: Basic Thread Pool for Background Tasks
- **New Concept**: Thread Pool Architecture & Task Queues  
- **Description**: Implement a fixed-size thread pool with a shared task queue.  
- **Learning Focus**: Efficient task distribution using mutexes and condition variables.  
- **Hardness Level**: 🔹 8/10  

---

### 📘 Project 9: Graceful Thread Termination
- **New Concept**: Cancellation & Detachment  
- **Description**: Demonstrate `pthread_cancel()` and `pthread_detach()` for lifecycle management.  
- **Learning Focus**: `pthread_cleanup_push/pop`, handling thread exit cleanly.  
- **Hardness Level**: 🔹 9/10  

---

### 📘 Project 10: Thread-Specific Data (TLS)
- **New Concept**: Thread-Local Storage  
- **Description**: Each thread maintains its own copy of a variable using `pthread_key_t`.  
- **Learning Focus**: `pthread_key_create()`, `pthread_setspecific()`, `pthread_getspecific()`.  
- **Hardness Level**: 🔹 9/10  

---

## 🏁 Project 11: Capstone - Concurrent Web Log Analyzer

### 🔄 Integrated Concepts:

- Thread Pool  
- Producer-Consumer Pattern  
- Mutexes & Condition Variables  
- Data Passing & Error Handling  
- Graceful Shutdown  
- *(Optional)* Reader-Writer Locks for shared result data

### 🧩 Description:

Build a multithreaded application to process a simulated web server log.

- **Log File**: Large simulated log entries  
- **Input Thread (Producer)**: Reads & parses lines, pushes them into a shared buffer  
- **Worker Thread Pool (Consumers)**: Analyze logs, update shared statistics  
- **Data Structures**: Protected by mutexes for thread-safe updates  
- **Shutdown**: All threads gracefully terminate after processing  
- **Report**: Main thread prints final statistics  

### 🎯 Learning Outcome:

Apply **all major pthread concepts** into a **functional, robust, and concurrent system**.
