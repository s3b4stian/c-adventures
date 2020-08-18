#include <stdio.h>

/**
 * Fibonacci series.
 * Recursive function.
 * 
 * @param int n
 * 
 * @return int
 */
int fib(int n)
{
    if (n <= 1) {
        return n;
    }

    return fib(n - 2) + fib(n - 1);
}

int mem[7];

/**
 * Fibonacci series.
 * Recursive function with memoization.
 * 
 * @param int n
 * 
 * @return int
 */
int fib_optimized(int n)
{
    if (n <= 1) {
        mem[n] = n;
        return n;
    }

    if (mem[n - 2] == -1) {
        mem[n - 2] = fib_optimized(n - 2);
    }

    if (mem[n - 1] == -1) {
        mem[n - 1] = fib_optimized(n - 1);
    }

    mem[n] = mem[n - 2] + mem[n - 1];

    return mem[n];
}


/**
 * Fibonacci series.
 * Iteractive function.
 * 
 * @param int n
 * 
 * @return int
 */
int fib_iteractive(int n)
{
    if (n <= 1) {
        return n;
    }

    int t0 = 0, t1 = 1, s;

    for (int i = 2; i <= n; i++) {
        s = t0 + t1;
        t0 = t1;
        t1 = s;
    }

    return s;
}


/**
 * Main.
 */
int main () {

    int n = 7;

    for (int i = 0; i < n; i++) {
        mem[i] = -1;
    }

    printf("Recursion:\tFibonacci of %d is: %d\n", n, fib(n));
    printf("Optimized:\tFibonacci of %d is: %d\n", n, fib_optimized(n));
    printf("Iteractive:\tFibonacci of %d is: %d\n", n, fib_iteractive(n));

    return 0;
}