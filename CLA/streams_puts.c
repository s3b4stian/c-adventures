#include <stdio.h>
#include <errno.h>
#include <string.h>

/**
 * Main.
 * Copy the content of two files, text file only.
 * Do not use for binary files.
 */
int main(int argc, char * argv[]) {
    FILE *inp, *out;
    char line[128];

    //check if we've got exactly three arguments
    if (argc != 3) {
        printf("usage: pname source_file target_file\n");
        return 1;
    }

    //check if we are able to open the source file
    if ((inp = fopen(argv[1], "rt")) == NULL) {
        printf("Cannot open %s\n", argv[1]);
        return 2;
    }

    //check if we are able to open the target file
    if ((out = fopen(argv[2], "wt")) == NULL) {
        printf("Cannot create %s\n", argv[2]);
        fclose(inp);
        return 3;
    }

    //we are going to read char by char until we reach EOF
    while((fgets(line, sizeof(line),inp)) != NULL) {
        if(fputs(line,out) == EOF) {
            break;
        }
    }   

    fclose(inp);
    fclose(out);

    return 0;
}