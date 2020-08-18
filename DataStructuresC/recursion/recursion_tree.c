#include <stdio.h>

/**
 * Recursive tree function.
 * Recursive statement is called more than one time inside the function.
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
        func(n - 1);
        // calling itself second time
        func(n - 1);
    }
}

/**
 * Main.
 */
int main () {

    int x = 3;

    // calling a recursive function
    func(x);

    return 0;
}