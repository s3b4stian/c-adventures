#include <stdio.h>

/**
 * Main.
 */
int main () {

    // array a of five integer elements
    // on stack
    
    // created and not initialized, values inside are garbage
    int a[5]; 
    // created and initialized, values inside 2, 4, 6, 8, 10
    int b[5] = {2, 4, 6, 8, 10};
    // created and initialized, values inside 2, 4, 0, 0, 0
    int c[5] = {2, 4};
    // created and initialized, all values inside are 0
    int d[5] = {0};
    // created and initialized, size determinated by values
    int e[] = {2, 4, 6, 8, 10};

    // array a of five integer elements
    // declared and initialized
    // on stack
    int x[5] = {27, 10, 16, 33, 5};

    // array element access
    for (int i = 0; i < 5; i++) {

        // print array value accessing to index
        printf("a[%d]: %d\n", i, x[i]);
        // print array value accessing to index, other notation
        printf("a[%d]: %d\n", i, i[x]);
        // print array value accessing to index, using pointer
        printf("a[%d]: %d\n", i, *(x + i));
    }

    // array address of the elements access
    for (int i = 0; i < 5; i++) {

        // print array value accessing to index
        printf("a[%d]: %u\n", i, &x[i]);

    }
}