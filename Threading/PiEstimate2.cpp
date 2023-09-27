/*
Name: <name>
Date: <date>
Description: <description>

To compile: g++ -lpthread PiEstimate2.cpp
*/

#include <iostream>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#define BILLION 1000000000L

using namespace std;

pthread_mutex_t lock;

#define NUMTHREADS 4

unsigned long throws;
unsigned long inside;

unsigned long seed = 5;

unsigned long myrand(){
    seed = seed * 7;
    
    //seed = seed << 1;
    seed = seed + 1;
    return seed;
}

void *toss(void *dummy) {
  unsigned long mythrows = 0;
  unsigned long myinside = 0;
  for (int i = 1; i <= 10000000; i++) {

    double x = (double)myrand() / ((double)RAND_MAX / 10);
    double y = (double)myrand() / ((double)RAND_MAX / 10);
    double dx = x - 5;
    double dy = y - 5;
    double d2 = dx * dx + dy * dy;
    mythrows++;
    if (d2 <= 25) {
      // inside
      myinside++;
    }
  }
  pthread_mutex_lock(&lock);
  throws = throws + mythrows;
  inside = inside + myinside;
  pthread_mutex_unlock(&lock);
  return NULL;
}

int main() {

  // Start clock
  struct timespec start;
  clock_gettime(CLOCK_MONOTONIC, &start);

  pthread_t thread[NUMTHREADS];
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  if (pthread_mutex_init(&lock, NULL) != 0) {
    cout << "\n mutex init has failed\n";
    return 1;
  }

  for (int i = 0; i < NUMTHREADS; i++) {
    pthread_create(&thread[i], &attr, toss, NULL);
  }

  for (int i = 0; i < NUMTHREADS; i++) {
    pthread_join(thread[i], NULL);
  }

  cout << "All done!" << endl;

  // toss(NULL);

  cout << throws << endl;
  cout << inside << endl;
  cout << (float)inside / throws << endl;
  cout << (float)inside / throws / 25 * 100 << endl;

  struct timespec end;
  clock_gettime(CLOCK_MONOTONIC, &end);
  long unsigned thread_elapsed =
      BILLION * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
  cout << "Threaded Elapsed: " << thread_elapsed << endl;

  // Non threaded version

  clock_gettime(CLOCK_MONOTONIC, &start);

  for (int i = 0; i < NUMTHREADS; i++) {
    toss(NULL);
  }

  clock_gettime(CLOCK_MONOTONIC, &end);
  long unsigned nonthread_elapsed =
      BILLION * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
  cout << "Non-Threaded Elapsed: " << nonthread_elapsed << endl;
  cout << throws << endl;
  cout << inside << endl;
  cout << (float)inside / throws << endl;
  cout << (float)inside / throws / 25 * 100 << endl;

  cout << "Threads are " << (double)nonthread_elapsed / (double)thread_elapsed
       << " as fast as non." << endl;
}