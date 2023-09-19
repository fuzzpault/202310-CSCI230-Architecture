/*
Name: Paul Talaga
Date: Sept 18, 2023
Description: Two threads doing work!

To compile: g++ -lpthread thread-global.cpp
*/

#include <chrono>
#include <iostream>
#include <pthread.h>

using namespace std;

// Example function
int thread_count = 0;
int ret = 0;

void *mysum(void *dummy) {
  cout << "Thread: " << thread_count << endl;
  thread_count++; // Global variable race condition!
  unsigned n = 1000;
  for(unsigned i = 1; i <= n; i++) {
    ret++;
  }
  cout << ret << endl;
  return NULL;
}

int main() {
  pthread_t thread;
  pthread_t thread2;

  pthread_attr_t attr;
  pthread_attr_init(&attr);


  pthread_create(&thread, &attr, mysum, NULL);
  pthread_create(&thread2, &attr, mysum, NULL);

  // Wait until each thread finishes before continuing
  pthread_join(thread, NULL);
  pthread_join(thread2, NULL);

  cout << "All done!" << endl;
  cout << "Ret: " << ret << endl;
}