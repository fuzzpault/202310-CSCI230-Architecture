/*
Name: Paul Talaga
Date: Sept 25, 2023
Description: Estimate pi via monte-carlo method.

To compile: g++ -lpthread PiEstimate.cpp
*/

#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define NUMTHREADS 5

unsigned long throws;
unsigned long inside;

void* toss(void* dummy) {
    for (int i = 1; i <= 10000000; i++){
        // Simulate throwing a dart at a 10x10 square
        double x = (double)rand() / ((double)RAND_MAX / 10);
        double y = (double)rand() / ((double)RAND_MAX / 10);
        // Calculate the distance from the dart to the center of the square
        double dx = x - 5;
        double dy = y - 5;
        // d2 is distance squared (so we don't have to do sqrt)
        double d2 = dx * dx + dy * dy;
        // Is the dart inside the circle?
        if(d2 <= 25){ // r=5, so r^2 = 25
            // inside hit!  keep track of number of insides
            inside++;
        }
        // Log this throw
        throws++;
        
    }
    return NULL;
}

int main() {
    /*
    // Threaded version
    pthread_t thread[NUMTHREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    for (int i = 0; i < NUMTHREADS; i++) {
        pthread_create(&thread[i], &attr, toss, NULL);
    }
    
    for (int i = 0; i < NUMTHREADS; i++) {
        pthread_join(thread[i], NULL);
    }
    
    cout << "All done!" << endl;
    */
    // Non-threaded version
    for(int i = 0; i < NUMTHREADS; i++){
        toss(NULL);
        cout << i + 1 << " of " << NUMTHREADS << " done" << endl;
    }
    
    cout << throws << endl;
    cout << inside << endl;
    cout << (double)inside / throws << endl;
    cout << (double)inside / throws / 25.0 * 100.0 << endl;
}