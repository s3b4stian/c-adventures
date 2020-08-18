#include <stdio.h>

/**
 * Calculate the power of first n natural numbers.
 * Recursive function.
 * 
 * @param int n
 * @param int exp
 * 
 * @return int
 */
int power(int n, int exp)
{
    if (exp == 0) {
        return 1;
    }

    return power(n, exp - 1) * n;
}

/**
 * Calculate the power of first n natural numbers.
 * Recursive optimized function.
 * 
 * @param int n
 * @param int exp
 * 
 * @return int
 */
int power_optimized(int n, int exp)
{
    if (exp == 0) {
        return 1;
    }

    if (exp % 2 == 0) {
        return power_optimized(n * n, exp / 2);
    }

    return n * power_optimized(n * n, (exp - 1) / 2);
}

/**
 * Calculate the power of first n natural numbers.
 * Iteractive function.
 * 
 * @param int n
 * @param int exp
 * 
 * @return int
 */
int power_iteractive(int n, int exp)
{
   
    int i, s = 1;

    for (i = 0; i < exp; i++) {
        s *= n;
    }

    return s;
}

/**
 * Main.
 */
int main () {

    int n = 2;
    int exp = 6;

    printf("Recursion:\t%d power %d is: %d\n", n, exp, power(n, exp));
    printf("Optimized:\t%d power %d is: %d\n", n, exp, power_optimized(n, exp));
    printf("Iteractive:\t%d power %d is: %d\n", n, exp, power_iteractive(n, exp));

    return 0;
}