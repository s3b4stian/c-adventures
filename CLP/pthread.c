#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREADS 8

void*  some_action(void * data) {
    char * msg = (char * ) data;
    //get the identity of the thread
    pthread_t self = pthread_self();
    //initialize the random number generator
    srand(self);
    
    printf("Thread %lxd started: \'%s\'\n", self, msg);
    //simulate the heavi work
    long delay = rand() % 5 + 1;
    sleep(delay);
    
    printf("Thread %lxd finished\n", self);
    
    //return the value of the thread
    return (void * ) delay;
}

//compile gcc pthread.c -lpthread
int main(void) {
    //declare an array of threads
    pthread_t threads[THREADS];
    char data[THREADS][20];

    printf("main() started...\n");
    
    for (int i = 0; i < THREADS; i++) {
        sprintf(data[i], "Thread #%d!", i + 1);
        //data[i] contains the data for every single thread
        //create threads
        //first argument is the pointer to pthread_t
        //pass &threads[i] or threads + 1 is equal
        pthread_create(threads + i, NULL, some_action, data[i]);
    }
    
    for (int i = 0; i < THREADS; i++) {
        long retval;
        //wait for all the threads to complete and print their results (the delay times)
        pthread_join(threads[i], (void * ) & retval);
        //retval is the delay passed to sleep in thread funciton
        printf("Thread %d joined: %ld\n", i + 1, retval);
    }
    
    return 0;
}