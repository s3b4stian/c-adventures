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
 * Calculate the factorial of first n natural numbers.
 * Iteractive function.
 * 
 * @param int n
 * 
 * @return int
 */
int factorial_iteractive(int n)
{
    if (n == 0) {
        return 1;
    }

    int i, s = 1;

    for (i = 1; i <= n; i++) {
        s *= i;
    }

    return s;
}

/**
 * Main.
 */
int main () {

    int x = 5;

    printf("Recursion:\tFactorial of first %d natural number is: %d\n", x, factorial(x));
    printf("Iteractive:\tFactorial of first %d natural number is: %d\n", x, factorial_iteractive(x));

    return 0;
}