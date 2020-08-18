#include <stdio.h>
#include <stdlib.h>

/**
 * Main.
 */
int main () {

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

    // declaring new pointer
    int *q;
    // allocate heap memory for ten integers
    q = (int*) malloc(10 * sizeof(int));
    // initialize all elements of q to zero
    for (int i = 0; i < 10; i++) {
        
        q[i] = 0;
    }
    
    // copy elements of p into q array
    for (int i = 0; i < 5; i++) {
        
        q[i] = p[i];
    }

    // release memory of p pointer (5 elements)
    free(p);
    // copy q pointer to p
    // now p point to q memory
    p = q;
    // delete q pointer
    q = NULL;


    for (int i = 0; i < 10; i++) {

        // value
        printf("p[%d]: %d\n", i, p[i]);
        // address
        printf("p[%d]: %u\n", i, &p[i]);
    }


    free(p);
    p = NULL;
}