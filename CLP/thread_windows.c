#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define THREADS 3

typedef struct {
    char msg[20];
    int retval;
} DATA;

DWORD WINAPI thread(LPVOID data)
{
    DATA *dat = (DATA *)data;
    DWORD self = GetCurrentThreadId();
    
    printf("Thread %xd started: \'%s\'\n", self, dat->msg);
    srand(self);
    
    DWORD delay = rand() % 5 + 1;
    
    Sleep(delay * 1000);
    
    printf("Thread %xd finished\n", self);
    
    dat->retval = delay;
    
    return 0;
}

int main(void)
{
    HANDLE threads[THREADS];
    DWORD thrdids[THREADS];
    DATA data[THREADS];

    printf("main() started...\n");
    for (int i = 0; i < THREADS; i++) {
        sprintf(data[i].msg, "Thread #%d!", i + 1);
        threads[i] = CreateThread(NULL, 0, thread, data + i, 0, thrdids + i);
    }

    for (int i = 0; i < THREADS; i++) {
        WaitForSingleObject(threads[i], INFINITE);
        printf("Thread %d completed: %ld\n", i + 1, data[i].retval);
    }
    
    return 0;
}