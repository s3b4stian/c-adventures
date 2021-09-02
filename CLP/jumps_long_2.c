#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

// create a cicle using long jump

void f(int x) {
    longjmp(buf, x);
}

int main(void) {
    int x = 0;
    
    if (setjmp(buf) < 5) {
        printf ("cicle: %d\n", x);
        f(++x);
    }
    
    printf ("final: %d\n", x);
    return 0;
}