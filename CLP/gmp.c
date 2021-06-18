#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(void) {
    //calculate factorial using standard types
    long long fact_p = 1;

    printf("[Factorial using long long]\n");
    for (int i = 1; i <= 50; i++) {
        fact_p *= i;
        printf ("%2d! = %lld\n", i, fact_p);
    }

    //calculate factorial using multi precision library
    printf("\n[Factorial using mpz_t]\n");
    mpz_t fact;
    mpz_init(fact);
    mpz_set_ui(fact, 1);

    for (int i = 1; i <= 50; i++) {
        mpz_mul_ui(fact, fact, i);
        char* str = mpz_get_str(NULL, 10, fact);
        printf("%2d! = %s\n", i, str);
        free(str);
    }

    return 0;
}