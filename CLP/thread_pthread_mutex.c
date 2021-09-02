#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREADS 50

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int sum = 0;
int cnt = 0;

void* thread(void * data) {
    int* p = (int * ) data;
    
     //get the identity of the thread
    pthread_t self = pthread_self();
    //initialize the random number generator
    srand(self);
    
    printf("Thread %lxd started\n", self, p);

    long delay = rand() % 5 + 1;
    sleep(delay);

    if ( * p % 2) {
        //lock the part of the critical code
        pthread_mutex_lock(&mutex);
        int s, c;
        s = sum;
        c = cnt;

        c = c + 1;
        s = s + *p;

        sum = s;
        cnt = c;
        //unlock the critical code
        pthread_mutex_unlock(&mutex);
    }

    printf("Thread %lxd finished: \'%d\'\n", self, sum);
    return NULL;
}

int main(void) {

    pthread_t threads[THREADS];
    int data[THREADS];

    //populate data
    for (int i = 0; i < THREADS; i++)
        data[i] = i + 1;
    
    for (int i = 0; i < THREADS; i++) {
        printf("Thread %d create\n", i + 1);
        pthread_create(threads + i, NULL, thread, data + i);
    }
    
    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
        printf("Thread %d joined\n", i + 1);
    }
    
    printf("Results: cnt=%d, sum=%d\n", cnt, sum);
    return 0;
}