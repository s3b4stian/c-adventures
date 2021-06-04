#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

    //declare a string
    char * s1 = "string";
    //duplicate the string to s2
    //new memory allocated
    char * s2 = strdup(s1);

    //strings are equals
    printf("%s\n", strcmp(s1, s2) ? "not equal" : "equal");
    //pointer to strings are different
    printf("%s\n", s1 == s2 ? "equal" : "not equal");

    //free the momory for the string created using strdup
    free(s2);

    //manipulate memory blocks
    double d1 = 1234.5678, d2 = 0.;

    memcpy (&d2, &d1, sizeof (double));
    printf ("%f\n", d2);

    return 0;
}