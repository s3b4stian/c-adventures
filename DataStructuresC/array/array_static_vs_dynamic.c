#include <stdio.h>
#include <stdlib.h>

/**
 * Main.
 */
int main () {

    // array a of five integer elements
    // on stack
    // created and not initialized, values inside are garbage
    // static array, memory allocated at compile time, array size cannot change
    int a[5];

    // poiter to integer
    // on stack
    int *p;

    // allocate heap memory for five integers
    // dynamic, size of array can be changed
    p = (int*) malloc(5 * sizeof(int));

    // assign values to array
    p[0] = 3;
    p[1] = 5;
    p[2] = 7;
    p[3] = 9;
    p[4] = 11;

    for (int i = 0; i < 5; i++) {

        // value
        printf("p[%d]: %d\n", i, p[i]);
        // address
        printf("p[%d]: %u\n", i, &p[i]);
    }

    // release memory
    free(p);
    p = NULL;
}