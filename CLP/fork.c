#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

char text[] = "ORIGINAL";

int main(void) {
    
    int v = fork();
    
    if (v == 0) {
        /* child */
        strcpy(text, "CHILD");
        printf("I'm a child: %s\n", text);
        return 0;
    } else if (v > 0) {
        /* parent */
        strcpy(text, "PARENT");
        printf("I'm a parent: %s\n", text);
        return 0;
    } else {
        /* failure */
        printf("fork() failed - %s\n", strerror(errno));
        return 1;
    }
}