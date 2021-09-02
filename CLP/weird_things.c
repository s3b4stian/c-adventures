
// The following is unspecified: the termination status returned to the hosted environment if the return type of main is not compatible with int
// The exit code returned by this program is unspecified.
float main (void)
{
    return 3.14159265359;
}

// The following is unspecified: the values of bytes that correspond to union members other than the one last stored into.
// The output of this program is unspecified.
#include <stdio.h>

int main (void)
{
    union {
        int i;
        short s;
    } un;

    un.s = -1;
    printf ("%d\n", un.i);

    return 0;
}

// The following is unspecified: whether two string literals result in distinct arrays.
// The output of this program is unspecified.
// Note: the program does not compare strings – it compares pointers to strings. 
// This leads us to ask whether or not two identical strings are stored in the memory in either one or two copies.
#include <stdio.h>

int main (void)
{
    printf ("%d\n", "abc" == "abc");
    return 0;
}

// The following is undefined: the value of a pointer to an object whose lifetime has ended is used.
// The output of the following program is undefined.
#include <stdio.h>

int *fun (void)
{
    int x = 2;
    return &x;
}

int main (void)
{
    printf ("%d\n", *fun ());
    return 0;
}

// The following is undefined: for a call to a function without a function prototype in scope, 
// the number of arguments does not equal the number of parameters.
// The output of the following program is undefined.
#include <stdio.h>

int main (void)
{
    printf ("%d\n", f());
    return 0;
}

int f (int x)
{
    return x;
}

// The following is undefined: the value of a pointer that refers to space deallocated by a call to the free or realloc function is used.
// The output of the following program is undefined.
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    int *p = malloc (sizeof (int));
    *p = 123;
    free (p);
    printf ("%d\n", *p);
    return 0;
}

// The following is undefined: an expression is shifted by a negative number 
// or by an amount greater than or equal to the width of the promoted expression.
// The output of the following program is undefined.
#include <stdio.h>

int main (void)
{
    printf ("%d\n", 1 << -1);
    return 0;
}

// The following is undefined: an attempt is made to copy an object to an overlapping object by use of a library function, 
// other than as explicitly allowed (e.g., memmove)”.
// The output of the following program is undefined.
#include <stdio.h>
#include <string.h>

int main (void)
{
    int t[] = { 1, 2, 3 };
    memcpy (t, t + 1, 2 * sizeof (int));
    printf ("%d %d %d\n", t[0], t[1], t[2]);
    return 0;
}

