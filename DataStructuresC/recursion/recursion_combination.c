#include <stdio.h>

/**
 * Calculate the factorial of first n natural numbers.
 * Recursive function.
 * 
 * @param int n
 * 
 * @return int
 */
int factorial(int n)
{
    if (n == 0) {
        return 1;
    }

    return factorial(n - 1) * n;
}

/**
 * Combination formula.
 * Using Factorials.
 * 
 * @param int n
 * 
 * @return int
 */
int nCr(int n, int r)
{
    int num, den;

    num = factorial(n);
    den = factorial(r) * factorial(n - r);

    return num / den;
}

/**
 * Combination formula.
 * Recursive function from Pascal's Trinagle
 * 
 * @param int n
 * 
 * @return int
 */
int nCr_tringle(int n, int r)
{
    if (r == 0 || n == r) {
        return 1;
    }

    return nCr_tringle(n - 1, r - 1) + nCr_tringle(n - 1, r);
}

/**
 * Main.
 */
int main () {

    int n = 4;
    int r = 2;

    printf("Factorial:\tCombination of n %d C r %d is: %d\n", n, r, nCr(n, r));
    printf("Recursion:\tCombination of n %d C r %d is: %d\n", n, r, nCr_tringle(n, r));

    return 0;
}