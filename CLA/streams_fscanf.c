#include <stdio.h>
#include <errno.h>
#include <string.h>

// numbers.txt
// 10
// 15
// 5
// 6
// 8
// 108
// 1024

/**
 * Main.
 * Read number from file and return them in increase order.
 */
int main(int argc, char * argv[]) {

    int numbers[1000];
    int aux;
    int numbersread = 0;
    int swapped;

    FILE * inp;

	//check arguments
    if (argc != 2) {
        printf("usage: pname input_file\n");
        return 1;
    }

	//check if possible open the file
    if ((inp = fopen(argv[1], "rt")) == NULL) {
        printf("Cannot open %s - %s\n", argv[1], strerror(errno));
        return 2;
    }

	//readfrom the string using fcanf to format the content
    while (fscanf(inp, "%d", & numbers[numbersread]) == 1) {
        numbersread++;
        if (numbersread == 1000) {
            break;
		}
    }

    fclose(inp);

	//check for no number read
    if (numbersread == 0) {
        printf("No numbers found in the files %s\n", argv[1]);
        return 3;
    }

	//ordering
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

    printf("The sorted values: ");

    for (int i = 0; i < numbersread; i++) {
        printf("%d ", numbers[i]);
    }

    printf("\n");

    return 0;
}