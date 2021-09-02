#include <stdio.h>
#include <fenv.h>
#include <math.h>
#include <float.h>


//The functions return zero on success and non-zero on error, unless stated otherwise.
// - the feclearexcept() function clears exceptions specified by the bit mask passed in an argument;
// - the fegetexceptflag() function stores (in the variable pointed to by the first argument) the current state of the exceptions specified by the second argument;
// - the feraiseexcept() function raises exceptions specified by the bit mask passed in an argument;
// - the fesetexceptflag() function sets the current state of exceptions pointed to by the first argument to the one specified by the second argument; 
//                         the value pointed to by flagp has to be fetched earlier by invoking fegetexceptflag() with all the second argument’s bits set; 
//                         the exceptions denoted in the second argument are not raised; note: the FENV_ACCESS pragma should be set to ON for the function;
// - the fetestexcept() function returns a bit mask reflecting those exceptions which are specified in the argument and are currently raised.


// These three functions operate on the floating-point environment - look at the editor.
// the functions return zero on success and non-zero on error;
// - fegetenv() stores the current state of the floating-point environment in a variable pointed to by the argument;
// - fesetenv() restores the state of the floating-point environment from the variable pointed to by the argument;
// - feupdateenv() acts like fesetenv() but currently raised exceptions are not cleared.



//check for the exception raised
#define _show_exc(x) printf(#x "=%s; ", fetestexcept(x) ? "ON" : "OFF")

#pragma STDC FENV_ACCESS ON

void show_exc(void)
{
    _show_exc(FE_DIVBYZERO);
    _show_exc(FE_INEXACT);
    _show_exc(FE_INVALID);
    _show_exc(FE_OVERFLOW);
    _show_exc(FE_UNDERFLOW);
    puts("\n");
}

//compile: gcc fenv.c -lm
int main(void)
{
    //no exceoptions
    printf("[No exception raised]\n");
    show_exc();

    //division by zero
    float x = 1.f, y = 0.f, z1 = x / y;
    printf("[Division by zero]\n");
    show_exc();

    //square root of negative number
    float z2 = sqrtf(-x);
    printf("[Square root of negative number]\n");
    show_exc();

    //this division will produce an inexact result
    float z3 = x / 1234.5678f;
    printf("[Division results in an inexact result]\n");
    show_exc();

    //get a result less than the minimal normalized value
    float z4 = x / FLT_MAX;
    z4 /= FLT_MAX;
    printf("[Underflow]\n");
    show_exc();

    //get a result grater than the maximal
    float z5 = x / FLT_MIN;
    z5 /= FLT_MIN;
    printf("[Overflow]\n");
    show_exc();

    fexcept_t flags;
    //save all exceptions
    fegetexceptflag(&flags, FE_ALL_EXCEPT);
    //clear all
    feclearexcept(FE_ALL_EXCEPT);
    printf("[All cleared]\n");
    show_exc();

    //explicitly raise two selected exceptions
    feraiseexcept(FE_OVERFLOW | FE_UNDERFLOW);
    printf("[Raise explicit]\n");
    show_exc();

    //set one more exception
    fesetexceptflag(&flags, FE_DIVBYZERO);
    printf("[Raise more]\n");
    show_exc();

    return 0;
}