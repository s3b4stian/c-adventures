#include <stdio.h>

/**
 * Recursive head function.
 * Recursive statement is the first inside the function.
 * All operation are performed at returning time.
 * Cannot be easily converted in loop.
 * 
 * @param int n
 * 
 * @return void
 */
void func(int n)
{
    if (n > 0) {
        
        // calling itself
        // recursive until if condition become false
        // decrement n every time the function call itself
        func(n - 1);

        // statement at returning time
        printf("%d\n", n);
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
    int i = 1;
    
    while (i <= n) {
        
        printf("%d\n", i);
        i++;
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