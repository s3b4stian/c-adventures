#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#define THREADS 10

mtx_t mutex;
int sum = 0;
int cnt = 0;

int thread(void * data) {
    
    int * p = (int * ) data;
    
    thrd_t self = thrd_current();
    unsigned long fakeid = * ((unsigned long * ) & self);

    printf("Thread %lx started\n", fakeid);

    struct timespec delay = {
        2,
        0
    };
    

    thrd_sleep( & delay, NULL);
    
    if ( * p % 2) {
        mtx_lock( & mutex);
        int s, c;
        s = sum;
        c = cnt;
        c = c + 1;
        s = s + * p;
        sum = s;
        cnt = c;
        mtx_unlock( & mutex);
    }
    
    printf("Thread %lx finished\n", fakeid);

    return 0;
}

int main(void) {

    thrd_t threads[THREADS];
    int data[THREADS];

    mtx_init(&mutex, mtx_plain);
    
    for (int i = 0; i < THREADS; i++)
        data[i] = i + 1;

    for (int i = 0; i < THREADS; i++) {
        thrd_create(threads + i, thread, data + i);
    }

    for (int i = 0; i < THREADS; i++) {
        thrd_join(threads[i], NULL);
    }
    
    printf("Results: cnt=%d, sum=%d\n", cnt, sum);
    
    mtx_destroy(&mutex);
    
    return 0;
}