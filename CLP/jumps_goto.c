#include <stdio.h>


// -  the label mentioned within the goto statement must be defined somewhere inside the enclosing function body; 
//    this also means that the goto statement must not lead to:
//      - outside a function;
//      - inside other function.
// -  any label defined within a particular function doesn’t have to be used in the goto statement.
// -  jump is possible backward and forward
// -  a goto statement may lead to the outside of a compound statement

int main (void)
{
    int i = 5;
back:
    while (i > 0) {
        
        int j = 5;
        
        while (j > 0) {
            
            printf ("%d %d\n", i, j);
            
            if (i == 4 && j == 4) {
                goto out;
            }
            j--;
	    }
        
        i--;
        goto back;
    }

out:
    return 0;
}