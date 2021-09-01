#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#define THREADS 5

int thread(void * data) {
    char * msg = (char * ) data;
    thrd_t self = thrd_current();
    
    unsigned long fakeid = * ((unsigned long * ) & self);
    
    srand(fakeid);
    
    struct timespec delay = {
        rand() % 5 + 1,
        0
    };
    
    printf("Thread %lx started: \'%s\'\n", fakeid, msg);
    thrd_sleep(&delay, NULL);
    printf("Thread %lx finished\n", fakeid);
    
    return delay.tv_sec;
}

//compile: gcc c11thread.c -lpthread
int main(void) {
    thrd_t threads[THREADS];
    char data[THREADS][20];

    printf("main() started...\n");

    for (int i = 0; i < THREADS; i++) {
        sprintf(data[i], "Thread #%d!", i + 1);
        thrd_create(threads + i, thread, data[i]);
    }

    for (int i = 0; i < THREADS; i++) {
        int retval;
        thrd_join(threads[i], & retval);
        printf("Thread %d joined: %ld\n", i + 1, retval);
    }

    return 0;
}