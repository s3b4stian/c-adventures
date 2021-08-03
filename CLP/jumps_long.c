#include <stdio.h>
#include <setjmp.h>

jmp_buf here;

void fun(int n)
{
    printf("fun() got %d\n", n);
    
    if (n != 0)
        longjmp(here, n);
   
    printf("fun() exits normally\n");
}

int main(void)
{
    int r = setjmp(here);
    
    if (r == 0) {
        printf("about to invoke fun() for the 1st time\n");

        fun(0);
        printf("returned from fun()\n");
        printf("about to invoke fun() for the 2nd time\n");

        fun(1);
        printf("returned from fun() again\n");
    }
    else {
        printf("long jump jumped here\n");
    }
    return 0;
}