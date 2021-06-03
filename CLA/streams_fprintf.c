#include <stdio.h>
#include <errno.h>
#include <string.h>

// file.txt
// ABCDEFGHIJKLMNOPQRSTUVWXYZ
// this is anoter line
// hello word

/**
 * Main.
 * Read a file with integer numbers then it write them in another file in increasing order.
 */
int main(int argc, char * argv[]) {
    int numbers[1000];
    int aux;
    int numbersread = 0;
    int swapped;
    FILE * inp, * out;

    if (argc != 3) {
        fprintf(stderr, "usage: pname source_file target_file\n");
        return 1;
    }

    if ((inp = fopen(argv[1], "rt")) == NULL) {
        fprintf(stderr, "Cannot open %s: %s\n", argv[1], strerror(errno));
        return 2;
    }

    if ((out = fopen(argv[2], "wt")) == NULL) {
        fprintf(stderr, "Cannot create %s: %s\n", argv[2], strerror(errno));
        fclose(inp);
        return 3;
    }

    while (fscanf(inp, "%d", & numbers[numbersread]) == 1) {
        numbersread++;
        if (numbersread == 1000) {
            break;
        }
    }

    fclose(inp);

    if (numbersread == 0) {
        printf("No numbers found in the file %s\n", argv[1]);
        return 3;
    }

    do {
        swapped = 0;
        for (int i = 0; i < numbersread - 1; i++) {
            if (numbers[i] > numbers[i + 1]) {
                swapped = 1;
                aux = numbers[i];
                numbers[i] = numbers[i + 1];
                numbers[i + 1] = aux;
            }
        }
    } while (swapped);

    for (int i = 0; i < numbersread; i++) {
        fprintf(out, "%d\n", numbers[i]);
    }

    printf("\n");

    fclose(out);

    return 0;
}