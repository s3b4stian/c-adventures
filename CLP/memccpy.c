#include <string.h>
#include <stdio.h>

int main (void)
{
    char s1[] = { 'a', 'b', 'c', 'd' };
    char s2[] = { 'x', 'x', 'x', 'x' };

    //copy 4 bytes from s1 to s2 and stop before if one of these bytes contains c char
    char *p = memccpy (s2, s1, 'c', 4);
    
    printf ("%c%c%c%c %c\n", s2[0], s2[1], s2[2], s2[3], *p);
    
    short int t1[] = { 1, 2, 3 };
    short int t2[] = { 0, 0, 0 };
    
    //The copying doesn’t reach the end of the t1 array.
    //There’s no element equal to zero in the t1 array.
    //There’s no short int value equal to zero in the t1, but there is a byte equal to zero. 
    //This is the second byte of the first element (assuming that the target platform uses the little-endian convention).
    //Don’t forget this basic memccpy() feature.
    //BE 00 01  00 02  00 03
    //LE 01 00  02 00  03 00
    char *p = memccpy (t2, t1, 0, sizeof (t1));
    
    printf ("%d %d %d %d\n", t2[0], t2[1], t2[2], *p);
    
    return 0;
}