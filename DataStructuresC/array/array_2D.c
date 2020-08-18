#include <stdio.h>
#include <stdlib.h>

/**
 * Main.
 */
int main () {

    // 1st method
    // declare an array with 3 rows and 4 columns
    int a[3][4];

    // create an array with 3 rows and 4 columns
    // initialize array with values
    int b[3][4] = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12}
    };


    // 2nd method
    // declare an array of 3 poiter to integer
    // on stack
    int *c[3];
    
    // allocate memory from heap for each element of pointer array
    // obtain a 3x4 array on heap
    c[0] = (int*) malloc(4 * sizeof(int));
    c[1] = (int*) malloc(4 * sizeof(int));
    c[2] = (int*) malloc(4 * sizeof(int));

    // assign value
    c[1][2] = 10;


    // 3rd method
    // double pointer
    int **d;
    // allocate memory from heap, note sizeof int pointer
    d = (int**) malloc(3 * sizeof(int *));
    // allocate memory from heap for each element of pointer array
    // obtain a 3x4 array on heap
    d[0] = (int*) malloc(4 * sizeof(int));
    d[1] = (int*) malloc(4 * sizeof(int));
    d[2] = (int*) malloc(4 * sizeof(int));


    free(c[0]);
    free(c[1]);
    free(c[2]);
 
    free(d[0]);
    free(d[1]);
    free(d[2]);
    free(d);
    d = NULL;
}