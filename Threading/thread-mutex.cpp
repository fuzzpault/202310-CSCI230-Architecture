/*
Name: Paul Talaga
Date: Sept 18, 2023
Description: Fix for race condition on global variable.
https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/
https://linux.die.net/man/3/pthread_mutex_lock

To compile: g++ -lpthread thread-mutex.cpp
*/

#include <chrono>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define NUMTHREADS 5

// Example function
int thread_count = 0;
int ret = 0;

pthread_mutex_t lock;

typedef struct thread_parms_t{
    int thread_id;
} thread_parms_t;

// A thread can only accept a single void* parameter and return a void* (pointers)
void* mysum(void* dummy) {
    thread_parms_t* parms = (thread_parms_t*)dummy;
    cout << "Thread: " << parms->thread_id << endl;
    int n = 10;
    int temp;
    
    for (int i = 1; i <= n; i++){
        pthread_mutex_lock(&lock);
        // Critical Section Start!
        temp = ret;
        temp++;
        usleep(1);
        ret = temp;
        // Critical Section End!
        pthread_mutex_unlock(&lock);
    }
    cout << "Done!: " << parms->thread_id << endl;
    return NULL;
}

int main() {
    // Setup array to hold thread information
    pthread_t thread[NUMTHREADS];

    // Thread attributes (we'll use defaults)
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // Verify we can get a mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        cout << "\n mutex init has failed\n";
        return 1;
    }

    // Setup the thread parameter structs
    thread_parms_t thread_parms[NUMTHREADS];

    
    for (int i = 0; i < NUMTHREADS; i++) {
        // Set something in the struct specific
        // to this thread.
        thread_parms[i].thread_id = i;
        pthread_create(&thread[i], &attr, mysum, &(thread_parms[i]));
    }
    
    for (int i = 0; i < NUMTHREADS; i++) {
        pthread_join(thread[i], NULL);
    }
    

    pthread_mutex_destroy(&lock);
    
    cout << "All done!" << endl;
    cout << "This should be: " << NUMTHREADS * 10 << endl;
    cout << "Ret: " << ret << endl;
}