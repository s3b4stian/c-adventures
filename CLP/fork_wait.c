#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


#define SECS 5

int main(void)
{
    int pid = fork();
    
    //if pid == 0 it is running a child
    if (pid == 0) {
        printf("Hi, I'm a child with PID=%d and I going to sleep for %d seconds...\n", getpid(), SECS);
        sleep(SECS);
        printf("Hi again, I'm a child and I woke up!\n");
        //child exit
        return 27;
    }
    else if (pid == -1) {
        fprintf(stderr, "Fork failed: %s\n", strerror(errno));
        return 1;
    }

    //if process isn't a child execution continue here
    printf("Hi, I'm a parent and I am waiting for my child to finish...\n");
    int status;
    int child = wait(&status);

    printf("PID=%d, retcode=%d\n", child, WEXITSTATUS(status));
    return 0;
}