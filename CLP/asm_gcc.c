#include <stdio.h>

int div2 (int x)
{
    int VAR = x;
    //AT&T convention
    asm(
        "movl %0,%%eax\n"
        "sarl $1,%%eax\n"
        "movl %%eax,%0\n"
        :"=m"(VAR) //list of output values
        :"m"(VAR)  //list of input values
        :"%eax"    //list of clobbered registers, gcc needs to know which of the registers lose their values during the execution of your code
    );
   
    return VAR;
}

int main(void)
{
  printf ("%d\n", div2 (24));
  printf ("%d\n", div2 (128));
  
  return 0;
}