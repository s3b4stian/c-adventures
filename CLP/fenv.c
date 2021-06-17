#include <stdio.h>
#include <fenv.h>
#include <math.h>
#include <float.h>

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