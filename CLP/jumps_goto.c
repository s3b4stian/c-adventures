#include <stdio.h>

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