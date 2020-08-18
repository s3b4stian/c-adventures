#include <stdio.h>

/**
 * Recursive nested function.
 * Recursive call take as argument another recursive call.
 * 
 * @param int n
 * 
 * @return int
 */
int func(int n)
{
    if (n > 100) {
        return n - 10;
    }

    // statement at calling time
    printf("%d\n", n);

    // calling itself
    // nested mode
    func(func(n + 11));
}


/**
 * Main.
 */
int main () {

    int x = 95;

    // calling a recursive function
    func(x);

    return 0;
}