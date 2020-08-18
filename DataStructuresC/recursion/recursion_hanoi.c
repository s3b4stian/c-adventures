#include <stdio.h>

/**
 * Tower of Hanoi.
 * Recursive function.
 * 
 * @param int n number of disks
 * @param int A first column, also from
 * @param int B second column
 * @param int C third column, also to
 * 
 * @return int
 */
int hanoi(int n, int A, int B, int C)
{
    if (n > 0) {
        hanoi(n - 1, A, C, B);
        printf("Moving disk %d from %d to %d\n", n, A, C);
        hanoi(n - 1, B, A, C);
    }
}

/**
 * Main.
 */
int main () {

    hanoi(4,1,2,3);

    return 0;
}