#include <stdio.h>
#include <errno.h>
#include <string.h>

/**
 * Main.
 * Copy the content of two files
 */
int main(int argc, char * argv[]) {
    FILE *inp, *out;
    int chr;

    //check if we've got exactly three arguments
    if (argc != 3) {
        printf("usage: pname source_file target_file\n");
        return 1;
    }

    //check if we are able to open the source file
    if ((inp = fopen(argv[1], "rb")) == NULL) {
        printf("Cannot open %s\n", argv[1]);
        return 2;
    }

    //check if we are able to open the target file
    if ((out = fopen(argv[2], "wb")) == NULL) {
        printf("Cannot create %s\n", argv[2]);
        fclose(inp);
        return 3;
    }

    //we are going to read char by char until we reach EOF
    while ((chr = fgetc(inp)) != EOF) {
        if (fputc(chr, out) == EOF) {
            break;
        }
    }   

    fclose(inp);
    fclose(out);

    return 0;
}