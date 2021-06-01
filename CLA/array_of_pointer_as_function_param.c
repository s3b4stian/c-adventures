#include <stdio.h>
#include <stdlib.h>

void printarrptr(int **t) {
    
    for(int i = 0; i<3; i++) {
        for(int j = 0; j<3; j++){ 
            printf("%d\t",t[i][j]);
        }

        printf("\n");
    }
}

/**
 * Main.
 */
int main(void) {

    //first version
    int *arrptr[3];
    
    for(int i = 0; i < 3; i++) {
        arrptr[i] = (int *) malloc(3 * sizeof(int));
        for(int j = 0; j < 3; j++) {
            arrptr[i][j] = (3 * i) + j + 1;
        }
    }

    printarrptr(arrptr);

    for(int i = 0; i < 3; i++) {
        free(arrptr[i]);
    }

    //second version
    //array of pointers
    int **ptrptr = malloc(3 * sizeof(int*));
    
    for(int i = 0; i < 3; i++) {
        //allocate memory for column
        ptrptr[i] = malloc(3 * sizeof(int));
        for(int j = 0; j < 3; j++) {
            ptrptr[i][j] = (3 * i) + j + 1;
        }
    }

    printarrptr(ptrptr);

    for(int i = 0; i < 3; i++) {
        free(ptrptr[i]);
    }
    free(ptrptr);


    return 0;
}