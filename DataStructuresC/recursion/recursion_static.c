#include <stdio.h>

/**
 * Recursive function.
 * 
 * @param int n
 * 
 * @return int
 */
int func(int n)
{
    if (n > 0) {
        // n at returning time
        return func(n - 1) + n;
    }
}

/**
 * Recursive function.
 * Use static value inside.
 * 
 * @param int n
 * 
 * @return int
 */
int func_static(int n)
{
    // if x was a global variable result would be the same
    static int x = 0;

    if (n > 0) {

        x++;
        // x a returning time
        return func_static(n - 1) + x;
    }
}

/**
 * Main.
 */
int main () {

    int x = 5;

    printf("%d\n", func(x));
    printf("%d\n", func_static(x));

    return 0;
}