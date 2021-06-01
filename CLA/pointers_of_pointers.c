#include <stdio.h>
#include <stdlib.h>

/**
 * Main.
 */
int main () {

    //declaring a 5 elements array of pointers of ints
    int rows = 5;
    int cols = 4;
    //pointer of pointers
    //declaring rows
    int **p;
    //important sizeof(pointer)
    p = malloc(rows * sizeof(int*));
    //declaring columns
    for (int r = 0; r < rows; r++) {
        //important sizeof(data type)
        p[r] = malloc (cols * sizeof (int));
    }

    //the same
    p[1][1] = 10;
    printf("p[1][1] = 10: %d\n", p[1][1]);
    //dereferencing the expression
    //p[0][1] = 20;
    *(*(p + 0) + 1) = 20;
    printf("*(*(p + 0) + 1): %d\n", *(*(p + 0) + 1));

    //with this type of array every row may has different length
    //free all pointers when they are no longer needed


    //10 element array of pointers
    int *array[10];

    //array as pointer to a 10-element array of int
    int (*array)[10];

    //variable array, which is a pointer to a 10-element array whose elements are pointers to ints
    int *(*array)[10];
}