#include <stdio.h>

struct stru {
    int i;
    float f;
};

int main(void) {
    //created but not initialized
    struct stru s;
    int * t, i;

    //initialization
    //from c99
    t = ((int[3]) {
        [2] = -1, 
        [1] = 0, 
        [0] = 1
    });

    //initialization
    //from c99
    s = ((struct stru) {
        .f = 2.0,
        .i = -1
    });

    for (i = 0; i < 3; i++)
        printf("%d ", t[i]);

    printf("\n%d %f\n", s.i, s.f);

    return 0;
}