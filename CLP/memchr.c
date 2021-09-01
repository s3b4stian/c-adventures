#include <string.h>
#include <stdio.h>


void print(char *b, char *p)
{
    if (p)
        // value of pointer p as char, difference n string first char address and position address
        printf ("'%c' [%ld]\n", *p, p - b);
    else
        printf ("(null)\n");
}

int main (void)
{
    char abc['Z' - 'A' + 1];
    int i;

    for (i = 'A'; i <= 'Z'; i++)
        abc[i - 'A'] = i;

    //search for a specific byte into memory and return the address
    print(abc, memchr(abc, 'C', sizeof (abc)));
    print(abc, memchr(abc, 'S', 10));
    print(abc, memchr(abc, 's', sizeof (abc)));
    
    // memrchr start the search from the end of the memory block

    return 0;
}