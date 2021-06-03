#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/**
 * Main.
 */
int main () {
    
    FILE *file;

    file = fopen("./file.txt","rt");
    
    if(file == NULL) {
        printf("File cannot be opened");
    }

    FILE *file2 = fopen("./file.txt","rt");
    
    if(file2 == NULL) { 
        switch(errno) {
            case ENOENT: printf("The file doesn't exist\n"); 
                 break;
            case EMFILE: printf("You've opened too many files\n"); 
                 break;
            default:     printf("The error number is %d\n",errno);
        }
    }
    
    return 0;
}