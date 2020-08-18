#include <stdio.h>

/**
 * Calculate the sum of first n natural numbers
 * Recursive function.
 * 
 * @param int n
 * 
 * @return int
 */
int sum(int n)
{
    if (n == 0) {
        return 0;
    }

    return sum(n - 1) + n;
}

/**
 * Calculate the sum of first n natural numbers
 * Iteractive function.
 * 
 * @param int n
 * 
 * @return int
 */
int sum_iteractive(int n)
{
    int i, s = 0;

    for (i = 1; i <= n; i++) {
        s += i;
    }

    return s;
}

/**
 * Calculate the sum of first n natural numbers
 * Time constant function.
 * 
 * @param int n
 * 
 * @return int
 */
int sum_time_constant(int n)
{
    return n * (n + 1) / 2;
}

/**
 * Main.
 */
int main () {

    int x = 7;

    printf("Recursion:\tSum of first %d natural number is: %d\n", x, sum(x));
    printf("Iteractive:\tSum of first %d natural number is: %d\n", x, sum_iteractive(x));
    printf("Time Constant:\tSum of first %d natural number is: %d\n", x, sum_time_constant(x));

    return 0;
}