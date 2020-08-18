#include <stdio.h>

/**
 * Calculate the Taylor series c of x using horner rule.
 * Recursive function.
 * 
 * @param int x
 * @param int n
 * 
 * @return double
 */
double c(int x, int n)
{
    static double s ;

    if (n == 0) {
        return s;
    }

    s = 1 + x * s / n;

    return c(x, n - 1);
}

/**
 * Calculate the Taylor series c of x using horner rule.
 * Iteractive function.
 * 
 * @param int x
 * @param int n
 * 
 * @return double
 */
double c_iteractive(int x, int n)
{
    double s = 1;

    for (; n > 0; n--) {

        s = 1 + x * s / n;
    }

    return s;
}

/**
 * Main.
 */
int main () {

    int n = 1;
    int x = 20;

    printf("Recursion:\tc %d of x %d Taylor serie is: %lf\n", n, x, c(n, x));
    printf("Iteractive:\tc %d of x %d Taylor serie is: %lf\n", n, x, c_iteractive(n, x));

    return 0;
}