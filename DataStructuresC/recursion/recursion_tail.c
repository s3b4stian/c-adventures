#include <stdio.h>

/**
 * Recursive tail function.
 * Recursive statement is the last inside the function.
 * All operation are performed at calling time.
 * 
 * @param int n
 * 
 * @return void
 */
void func(int n)
{
    if (n > 0) {

        // statement at calling time
        printf("%d\n", n);

        // calling itself
        // recursive until if condition become false
        // decrement n every time the function call itself
        func(n - 1);
    }
}

/**
 * Iteractive function.
 * 
 * @param int n
 * 
 * @return void
 */
void func_iteractive(int n)
{
    while (n > 0) {
        printf("%d\n", n);
        n--;
    }
}

/**
 * Main.
 */
int main () {

    int x = 3;

    // calling a recursive function
    func(x);

    printf("\n");

    // calling iteractive function
    func_iteractive(x);

    return 0;
}