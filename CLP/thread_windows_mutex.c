#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define THREADS 50

HANDLE mutex;
int sum = 0;
int cnt = 0;

DWORD WINAPI
thread(LPVOID *data)
{
    int *p = (int *)data;

    Sleep(2000);

    if (*p % 2) {
        
        WaitForSingleObject(mutex, INFINITE);

        int s, c;
        s = sum;
        c = cnt;
        c = c + 1;
        s = s + *p;
        sum = s;
        cnt = c;

        ReleaseMutex(mutex);
    }

    return 0;
}

int main(void)
{
    HANDLE threads[THREADS];
    DWORD thrdids[THREADS];
    int data[THREADS];

    mutex = CreateMutex(NULL, FALSE, NULL);
    
    for (int i = 0; i < THREADS; i++) {
        data[i] = i + 1;
    }

    for (int i = 0; i < THREADS; i++) {

        threads[i] = CreateThread(NULL, 0, thread, data + i, 0, thrdids + i);
        
        if (threads[i] == NULL) {
            printf("ERROR %d\n", i);
            exit(0);
        }
    }

    WaitForMultipleObjects(THREADS, threads, TRUE, INFINITE);
    
    for (int i = 0; i < THREADS; i++) {
        CloseHandle(threads[i]);
    }
    
    printf("Results: cnt=%d, sum=%d\n", cnt, sum);
    
    CloseHandle(mutex);
    
    return 0;
}