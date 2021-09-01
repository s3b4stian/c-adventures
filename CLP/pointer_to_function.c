#include <string.h>
#include <stdio.h>

int sum (int p1, int p2)
{
    return (p1) + (p2);
}

int main(void) {
    //pointer to function that has as args two ints and return an int
    int (*sum_ptr) (int, int);
    sum_ptr = sum;

    printf("[%d]", sum_ptr(10,5));
}