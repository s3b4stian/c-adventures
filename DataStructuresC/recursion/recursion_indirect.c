#include <stdio.h>

void func_b(int n);

/**
 * Print numbers starting from argument to zero.
 * Recursive indirect function.
 * 
 * @param int n
 * 
 * @return void
 */
void func_a(int n)
{
    if (n > 0) {

        // statement at calling time
        printf("%d\n", n);

        // calling itself
        func_b(n - 1);
    }
}

/**
 * Print numbers divided by two starting from argument to one.
 * Recursive indirect function.
 * 
 * @param int n
 * 
 * @return void
 */
void func_b(int n)
{
    if (n > 1) {

        // statement at calling time
        printf("%d\n", n);

        // calling itself
        func_a(n / 2);
    }
}

/**
 * Main.
 */
int main () {

    int x = 20;

    // calling a recursive function
    func_a(x);

    return 0;
}