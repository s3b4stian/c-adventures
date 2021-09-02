
#include <stdio.h>

//float
//sign (bits): 	                1
//exponent (bits): 	            8
//significand (bits): 	        23
//bits in total: 	            32	
//precision: 	                7 ÷ 8 decimal significant digits
//range (absolute values):      1.18*10^-38 ÷ 3.4*10^38 and 0.0

//double
//sign (bits): 	                1
//exponent (bits): 	            11
//significand (bits): 	        52
//bits in total: 	            64	
//precision: 	                15 ÷ 16 decimal significant digits
//range (absolute values): 	    2.23*10^-308 ÷ 1.8*10^308 and 0.0

//long double
//sign (bits): 	                1
//exponent (bits): 	            15
//significand (bits): 	        112
//bits in total: 	            128	
//precision: 	                34 ÷ 35 decimal significant digits
//range (absolute values): 	    3.362103*10^-4932 ÷ 1.189731*10^4932 and 0.0


//IEEE 754 requires that the significand should be normalized if possible,
//normalization means that the first significand bit should not be zero
//first significand bit set to 1

//IEEE 754 says that any result of any floating-point operation should not differ from the actual result by more than half (1/2) ULP.
//Most currently used systems and library functions provide results with an accuracy of range 1 - half(1/2) ULP.

int main(void)
{
    //output differ
    printf("%f\n", 16777216.f + 1.f);
    printf("%f\n", 16777216. + 1.);

    float x = 1.f, y = 0.f, z;

    z = x / y; // result inf
    printf ("%f\n", z);

    z = -x / y; //result -inf
    printf ("%f\n", z);

    return 0;
}