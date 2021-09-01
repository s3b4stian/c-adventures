#include <stdarg.h>
#include <stdio.h>

int max(int n, va_list vals)
{
    int m = va_arg(vals, int);
    
    while (--n > 0) {
        int k = va_arg(vals, int);
        
        if (k > m) {
            m = k;
        }
    }
  
    return m;
}

int va_max(int n, ...)
{
    va_list l;
    va_start(l, n);
    int r = max(n, l);
    va_end(l);
    return r;
}

int main(void)
{
    int x = va_max(3, 1, 2, 3);
    printf("%d\n", x);
    return 0;
}