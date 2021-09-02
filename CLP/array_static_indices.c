#include <stdio.h>

//tell the compiler that the t param must be at least of 4 elemets
//I didn't find a way to trigger a warning or an error

//int f(int matrix[static 2][2]) { ... } //ok
//int f(int matrix[static 2][static 2]) { ... } //not ok

int fun (char t[static 4])
{
    return t == NULL;
}

int main (void)
{
    fun("ab");
    fun("abc");
    char a[10];
    fun(a);
    fun(NULL);
    
    return 0;
}

