#include <stdio.h>

/**
 * Calculate the Taylor series c of x.
 * Recursive function.
 * 
 * @param int x
 * @param int n
 * 
 * @return double
 */
double c(int x, int n)
{
    static double p = 1, f = 1;

    double r = 0;

    if (n == 0) {
        return 1;
    }

    r = c(x, n - 1); // recursion call
    p = p * x; // power
    f = f * n; // factorial

    return r + p / f;
}


/**
 * Main.
 */
int main () {

    int n = 4;
    int x = 10;

    printf("Recursion:\tc %d of x %d Taylor serie is: %lf\n", n, x, c(n, x));

    return 0;
}