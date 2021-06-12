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
    printf("Parent forks...\n");

    //fork the process 3 times
    for (int c = 0; c < CHILDREN; c++) {
        
        int pid = fork();
        //every loop if the pid is 0
        //start the execution of the code belongs the child process
        if (pid == 0) {
            srand(getpid());
            int secs = rand() % SECS + 1;
            printf("Child: PID=%d sleep=%d sec\n", getpid(), secs);
            //in real life this is work!
            sleep(secs);
            printf("Child: PID=%d woke up!\n", getpid());
            //exit from child process
            return 27;
        } else if (pid == -1) {
            fprintf(stderr, "Fork failed: %s\n", strerror(errno));
            return 1;
        }
    }

    //parent code
    printf("Parent is waiting...\n");
    
    for (int c = 0; c < CHILDREN; c++) {
        int status; 
        int child = wait(&status);
        printf("Parent: child exited: PID=%d, retcode=%d\n", child, WEXITSTATUS(status));
    }
    
    return 0;
}