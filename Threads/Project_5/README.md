## Project 5: Producer-Consumer with a Bounded Buffer

### **New Concept:** Inter-Thread Communication & Signaling using Condition Variables (`pthread_cond_t`)

This project tackles the classic **Producer-Consumer problem**, a fundamental pattern in concurrent programming. It demonstrates how two threads (a producer and a consumer) can safely and efficiently communicate through a shared, fixed-size data structure called a **bounded buffer**.

#### **Key Concepts Illustrated:**

* **Bounded Buffer:** A fixed-size buffer (implemented as a circular array) where the producer places items and the consumer takes them.
* **Producer:** A thread that generates data items and attempts to add them to the buffer. If the buffer is full, the producer must wait.
* **Consumer:** A thread that consumes data items from the buffer. If the buffer is empty, the consumer must wait.
* **Mutexes (`pthread_mutex_t`):** Used to ensure **mutual exclusion**, protecting the shared buffer (and its `count`, `in`, `out` variables) from race conditions when either thread modifies it. Only one thread can access the buffer at a time.
* **Condition Variables (`pthread_cond_t`):** The crucial mechanism for **efficient inter-thread communication and synchronization**.
    * `buffer_not_full`: The producer waits on this condition if the buffer is full. It's signaled by the consumer when space becomes available.
    * `buffer_not_empty`: The consumer waits on this condition if the buffer is empty. It's signaled by the producer when a new item is added.
* **`pthread_cond_wait()`:** This function is vital. When a thread calls it (e.g., producer finding the buffer full), it **atomically releases the mutex** and puts the thread to sleep, preventing busy-waiting. When signaled, it automatically re-acquires the mutex before resuming.
* **`pthread_cond_signal()`:** Used to wake up one thread waiting on a specific condition variable.

#### **What the Code Does:**

This C program simulates the producer-consumer problem:
1.  A `main` thread sets up a shared integer array (the bounded buffer) and initializes a mutex and two condition variables.
2.  It creates a `producer_thread_func` and a `consumer_thread_func`.
3.  The **Producer Thread** generates `NUM_OF_ITEM_TO_PRODUCE` integer items sequentially.
    * It acquires the `buffer_mutex`.
    * If the `count` of items in the buffer equals `BUFFER_SIZE`, it calls `pthread_cond_wait(&buffer_not_full, &buffer_mutex)` to wait until the consumer makes space.
    * Once space is available, it adds an item to `shared_buffer` using the `in` index (and updates `in` circularly).
    * It increments `count`.
    * It signals `buffer_not_empty` to potentially wake up a waiting consumer.
    * It releases the `buffer_mutex`.
4.  The **Consumer Thread** attempts to consume `NUM_OF_ITEM_TO_PRODUCE` items.
    * It acquires the `buffer_mutex`.
    * If the `count` of items is `0`, it calls `pthread_cond_wait(&buffer_not_empty, &buffer_mutex)` to wait until the producer adds an item.
    * Once an item is available, it retrieves it from `shared_buffer` using the `out` index (and updates `out` circularly).
    * It decrements `count`.
    * It signals `buffer_not_full` to potentially wake up a waiting producer.
    * It releases the `buffer_mutex`.
5.  The `main` thread waits for both producer and consumer threads to complete using `pthread_join()` and then cleans up all allocated resources (buffer memory, mutex, condition variables).

#### **Learning Focus:**

* Implementing efficient inter-thread communication.
* Understanding the proper use of `pthread_cond_wait()` with a `while` loop to avoid busy-waiting and handle spurious wakeups.
* Applying mutexes and condition variables together to build complex synchronization patterns.
* Managing circular buffer logic (`% BUFFER_SIZE`).
* Ensuring correct program termination when threads rely on each other's actions.

#### **Hardness Level:** 5/10 (A significant step up from basic mutex usage)

---