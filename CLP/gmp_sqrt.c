#include <stdio.h>
#include <math.h>
#include <gmp.h>

#define N 10
#define	PREC 1024

int main(void) {
    float val_m = 2.;

    printf("[Square root of square root 10 times using math.h]\n");

    for (int i = 0; i < N; i++)
        val_m = sqrtf(val_m);
    for (int i = 0; i < N; i++)
        val_m *= val_m;

    printf("%.23e\n\n", fabs(val_m - 2.));

    printf("[Square root of square root 10 times using gmp.h]\n");

    mpf_t val, two, dif;
    mpf_init2(val, PREC);
    mpf_init2(two, PREC);
    mpf_set_d(val, 2.);
    mpf_set(two, val);

    for (int i = 0; i < N; i++)
        mpf_sqrt(val, val);
    for (int i = 0; i < N; i++)
        mpf_mul(val, val, val);

    mpf_init2(dif, PREC);
    mpf_sub(dif, val, two);
    mpf_abs(dif, dif);

    double difd = mpf_get_d(dif);

    printf("%.23e\n", difd);

    return 0;
}