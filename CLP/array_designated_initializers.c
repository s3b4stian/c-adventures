#include <stdio.h>

int main(void) {
    
    //the designated array initializer allows you to enumerate only the elements which are important to you,
    //and you can enumerate them in any order.
    // - all omitted array elements are initialized to zero (or its equivalent)
    // - all given indices must fit the array’s size
    // - all indices must be unique
    int vec[3] = {
        [2] = 1,
        [0] = 3
    };
    
    int i;

    for (i = 0; i < 3; i++)
        printf("%d ", vec[i]);
    
    printf("\n");

    return 0;
}