#include <stdio.h>
#include <setjmp.h>

#define ERROR (-1)

jmp_buf retpoint;

int f3(int x)
{
    if (x < 0)
        longjmp(retpoint, ERROR); // retopoint -1

    return x;
}

int f2(int x)
{
    int r = f3(x); // call f3

    return r;
}

int f1(int x)
{
    int r = f2(x); // call f2

    return r;
}

int main(void)
{
    if (setjmp(retpoint) == 0) { // enter here
        printf("%d\n", f1(2)); // all ok
        printf("%d\n", f1(-2)); // long jump
    } 
    else {
        printf("ERROR!\n");
        
    }
    return 0;
}