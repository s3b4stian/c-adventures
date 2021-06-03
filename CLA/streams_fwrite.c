#include <stdio.h>
#include <errno.h>
#include <string.h>

// file.txt
// ABCDEFGHIJKLMNOPQRSTUVWXYZ
// this is anoter line
// hello word

/**
 * Main.
 * Copy the content of two files usinf fread and fwrite.
 */
int main(int argc, char * argv[]) {
    FILE *inp, *out;
    char buffer[16384]; //16 kilobytes
    int read, written;

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

    do {
        //read one byte for sizeof(buffer) from inp
        read = fread(buffer, 1, sizeof(buffer), inp);
        if (read) {
            //write one byte for previous readed to out
            written = fwrite(buffer, 1, read, out);
        }
    } while (read && written);
    
    fclose(inp);
    fclose(out);
    
    return 0;
}