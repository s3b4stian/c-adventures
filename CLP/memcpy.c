#include <string.h>
#include <stdio.h>

typedef struct {
    int i;
    char c;
} str_t;

int main(void) {

    // aggregate date
    str_t tab1[5], tab2[5];

    for (int i = 0; i < 5; i++) {
        tab1[i].i = i;
        tab1[i].c = 'a' + i;
    }

    memcpy(tab2, tab1, sizeof(tab2));

    for (int i = 0; i < 5; i++) {
        printf("%d %c\n", tab2[i].i, tab2[i].c);
    }

    // scalar data
    double d1 = 1234.5678, d2 = 0.;

    memcpy (&d2, &d1, sizeof (double));
    
    printf ("%f\n", d2);

    return 0;
}