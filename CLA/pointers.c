#include <stdio.h>
#include <stdlib.h>

/**
 * Main.
 */
int main () {

    //declaring a pointer
    int *p;

    //make a pointer null
    //two wais
    p = 0;
    p = NULL; // NULL is a macro


    int ivar, *ptr;
    ivar = 2;
    //now ptr point to ivar
    //& operator return memory address of ivar
    ptr = &ivar;
    //assign the value pointed from pointer to pvar
    //* operator is the deferencer of the pointer
    int pvar = *ptr;

    //pointers and variable values
    printf("ivar:  %i\n", ivar);
    printf("&ivar: %x\n", &ivar);
    printf("ptr:   %x\n", ptr);
    printf("*ptr:  %i\n", *ptr);
    printf("pvar:  %i\n", pvar);

    //array pointers
    int *aptr = NULL;
    int arr[4] = {10,20,30,40};

    //make pointer to point the first element of the array
    aptr = &arr[0];
    printf("aptr = &arr[0];  %x %x\n", aptr, &arr[0]);
    aptr = arr;
    printf("aptr = arr;  %x %x\n", aptr, arr);

    //incrementing a pointer to array permit to slide the array
    //*(++aptr) is equal to incremente the pointer the deference it
    printf("aptr: %d\n", *aptr);
    printf("aptr: %d\n", *(++aptr));
    printf("aptr: %d\n", *(++aptr));
    printf("aptr: %d\n", *(++aptr));
    //return to the first element of the pointer
    printf("aptr: %d\n", *(aptr-3));
}