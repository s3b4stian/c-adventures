#include <stdio.h>
#include <stdlib.h>

#define N 5

void print(float * t, int n) {
    
    for (int i = 0; i < n; i++) {
        printf("%f; ", t[i]);
    }

    printf("\n");
}

int main(void) {
    
    //malloc, one argument, bytes
    float * t1 = malloc(N * sizeof(float));
    //calloc, two arguments, quantity and size of quantity
    float * t2 = calloc(N, sizeof(float));

    print(t1, N);
    print(t2, N);

    free(t1);
    free(t2);

    return 0;
}