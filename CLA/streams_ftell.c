#include <stdio.h>
#include <errno.h>
#include <string.h>

/**
 * Main.
 * Return the size of a file.
 */
int main(int argc, char * argv[]) {
    FILE * file;
    long size;

    if (argc != 2) {
        fprintf(stderr, "usage: pname file_name\n");
        return 1;
    }

    if ((file = fopen(argv[1], "rt")) == NULL) {
        fprintf(stderr, "Cannot open %s: %s\n", argv[1], strerror(errno));
        return 2;
    }
    
    //attempt to skip to the end of file
    if (fseek(file, 0, SEEK_END)) {
        if (errno == EBADF)
            fprintf(stderr, "The file has no size: %s\n", argv[1]);
        else
            fprintf(stderr, "Error in fseek: #%d\n", errno);
    }
    else {
        //get the current position in the stream
        size = ftell(file);
        printf("File: %s size: %d\n", argv[1], size);
    }

    fclose(file);

    return 0;
}