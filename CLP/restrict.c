//The keyword is actually a promise. 
//The programmer using the qualifier promises the compiler that the entity pointed to by the pointer, 
//or by expression making use of the pointer (like ptr + 2 or ptr[2]), 
//is not accessible in any other way. 
//Knowing this, the compiler is able to produce more effective code. 
//But there’s a catch: if you break your promise, the code may behave erratically. 
//Don’t toss your words into the wind.


//gcc 11.2 -O1

/*
inc:
        mov     eax, DWORD PTR [rsi]
        add     eax, DWORD PTR [rdi]
        mov     DWORD PTR [rdi], eax
        add     eax, DWORD PTR [rdx]
        mov     DWORD PTR [rdi], eax
        add     eax, DWORD PTR [rcx]
        mov     DWORD PTR [rdi], eax
        ret
*/
void inc (int *v, int *x, int *y, int *z)
{
    *v += *x;
    *v += *y;
    *v += *z;
}

/*
inc:
        mov     eax, DWORD PTR [rsi]
        add     eax, DWORD PTR [rdi]
        add     eax, DWORD PTR [rdx]
        add     eax, DWORD PTR [rcx]
        mov     DWORD PTR [rdi], eax
        ret
*/
void inc (int * restrict v, int *x, int *y, int *z)
{
    *v += *x;
    *v += *y;
    *v += *z;
}