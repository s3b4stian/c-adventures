#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SECS 10
#define CHILDREN 3

int main(void)
{
    int c;
    int pids[CHILDREN];

    for (c = 0; c < CHILDREN; c++) {
        
        int pid = fork();
        
        if (pid == 0) {
            srand(getpid());
            int secs = rand() % SECS + 1;
            printf("Child: PID=%d sleep=%d sec\n", getpid(), secs);
            sleep(secs);
            printf("Child: PID=%d woke up!\n", getpid());
            return 27;
        }
        else if (pid == -1) {
            fprintf(stderr, "Fork failed: %s\n", strerror(errno));
            return 1;
        }
        printf("Parent: forked child #%d\n", pid);
        pids[c] = pid;
    }
    
    for (c = 0; c < CHILDREN; c++) {
        printf("Parent: waiting for child #%d\n", c);
        int status, child = waitpid(pids[c], &status, 0);
        printf("Parent: child #%d exited: PID=%d, retcode=%d\n",
            c, child, WEXITSTATUS(status));
    }

    return 0;
}