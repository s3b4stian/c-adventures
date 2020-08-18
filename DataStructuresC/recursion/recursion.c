#include <stdio.h>

/**
 * Print numbers starting from argument to zero.
 * Recursive function
 * 
 * @param int n
 * 
 * @return void
 */
void to_zero(int n)
{
    if (n > 0) {

        // statement at calling time
        printf("%d\n", n);

        // calling itself
        // recursive until if condition become false
        // decrement n every time the function call itself
        to_zero(n - 1);
    }
}

/**
 * Print numbers starting from argument to zero.
 * Recursive function
 * 
 * @param int n
 * 
 * @return void
 */
void to_zero_tail(int n)
{
    if (n > 0) {

        // calling itself
        // recursive until if condition become false
        // decrement n every time the function call itself
        to_zero_tail(n - 1);

        // statement at returning time
        printf("%d\n", n);
    }
}

/**
 * Main.
 */
int main () {

    int x = 3;

    // calling a recursive function
    to_zero(x);

    printf("\n");

    // calling a recursive function
    to_zero_tail(x);

    return 0;
}