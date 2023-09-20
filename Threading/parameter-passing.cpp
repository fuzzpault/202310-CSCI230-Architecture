/*
Name: Paul Talaga
Date: Sept 20, 2023
Description: Demonstrating passing paramters to
    threads via a struct.

To compile: g++ -lpthread parameter-passing.cpp
*/

#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define NUMTHREADS 5

pthread_mutex_t lock;

int ret;

struct thread_t{
    int thread_id;
    int from;
    int to;
};

void* mysum(void* dummy) {
    thread_t* p = (thread_t*)dummy;
    cout << "ID: " << p->thread_id << endl;
    int temp;
    for (int i = 1; i <= 10; i++){
        pthread_mutex_lock(&lock);
        // Critical Section Start!
        temp = ret;
        temp++;
        usleep(1);
        ret = temp;
        // Critical Section End!
        pthread_mutex_unlock(&lock);
    }
    p->to = temp;
    return NULL;
}

int main() {
    ret = 0;
    
    pthread_t thread[NUMTHREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_mutex_init(&lock, NULL);

    thread_t parms[NUMTHREADS];
    
    for (int i = 0; i < NUMTHREADS; i++) {
        parms[i].thread_id = i;
        parms[i].from = i * 2;
        pthread_create(&thread[i], &attr, mysum, &parms[i]);
    }
    
    for (int i = 0; i < NUMTHREADS; i++) {
        pthread_join(thread[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    
    cout << "Ret: " << ret << endl;
    cout << "All done!" << endl;
}