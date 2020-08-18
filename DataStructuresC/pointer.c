#include <stdio.h>
#include <stdlib.h>

/**
 * Main.
 */
int main () {

    // declare integer variable a initilized to ten
    // on stack
    int a = 10;

    // declaring pointer p
    // on stack
    int *p;

    // initialize p with the address of a
    p = &a;

    // print the value of a
    printf("a: %d\n", a);
    // print the memory address of a in p
    printf("a: %X\n", p);
    // print the value of a through p
    // dereferencing
    printf("a: %d\n", *p);

    // declare pointer b
    // on stack
    int *b;

    // allocate heap memory for 10 int values
    // type casting required becaouse malloc return pointer to void
    b = (int *) malloc(10 * sizeof(int));

    // free memory reserverd for b
    free(b);
}