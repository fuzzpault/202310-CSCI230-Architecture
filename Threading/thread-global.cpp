/*
Name: Paul Talaga
Date: Sept 18, 2023
Description: Race condition on global variable.

To compile: g++ -lpthread thread-global.cpp
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

void* mysum(void* dummy) {
    // cout << "Thread: " << thread_count << endl;
    // thread_count++;
    int n = 10;
    int temp;
    
    for (int i = 1; i <= n; i++){
        temp = ret;
        temp++;
        usleep(1);
        ret = temp;
    }
    return NULL;
}

int main() {
    pthread_t thread[NUMTHREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    for (int i = 0; i < NUMTHREADS; i++) {
        pthread_create(&thread[i], &attr, mysum, NULL);
    }
    
    for (int i = 0; i < NUMTHREADS; i++) {
        pthread_join(thread[i], NULL);
    }
    
    /*for(int i = 0; i < NUMTHREADS; i++){
    mysum(NULL);
    }*/
    
    cout << "All done!" << endl;
    cout << "This should be: " << NUMTHREADS * 10 << endl;
    cout << "Ret: " << ret << endl;
}