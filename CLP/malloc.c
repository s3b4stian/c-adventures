#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/**
 * Main.
 * It allocates a small memory block (the smallest possible) 
 * and checks the alignment of the resulting pointer – it tries to divide 
 * the pointer by 2, 4, 8, .. 32 and announces whether or not the remainder is equal to zero.
 */
int main () {

    //declare void pointer
    void *p = malloc (1);
    //assign it to l using casting
    unsigned long l = (unsigned long) p;
    
    free(p);

    printf ("%p\n", p);
    
    for (int i = 2; i <= 64; i <<= 1) {
        printf ("%02d -> %s\n", i, (l % i) ? "no" : "yes");
    }
    
    return 0;
}