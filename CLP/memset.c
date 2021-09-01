#include <string.h>
#include <stdio.h>

int main (void)
{
    short int t[4];

    // set all bytes to 0
    memset(t, 0, sizeof (t));
    printf("%d %d %d %d\n", t[0], t[1], t[2], t[3]);
    
    // set all bytes to 1
    // this operation makes print function to show 257 257 257 257
    // beacuse using shor int there are two bytes, all set to 1
    // 0x0101
    memset(t, 1, sizeof (t));
    printf("%d %d %d %d\n", t[0], t[1], t[2], t[3]);

    return 0;
}