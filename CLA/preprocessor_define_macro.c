#include <stdio.h>

#define SQR(x)	(x * x)
#define SQR1(x)	((x) * (x))

#define	MAX(X,Y)	(((X) > (Y)) ? (X) : (Y))

#define QUOTE(X) #X

#define SNAP(X) printf("variable "#X" = %d\n",X)

#define GLUE(X,Y)  X##Y

//gcc -E preprocessor_define_macro.c
//shows preprocessor result
int main(void) {
	
    int i = 4;
    int s = SQR(i);

    i = 4;
    s = SQR1(i + 1);

    i = 4;
    s = SQR1(i++);

    int var1 = 100;
    int var2 = 200;

    int res = MAX(var1, var2);

    puts(QUOTE(this is a test to string));


    int test = 0;
    int counter = 1;
    int SheepTotal = 261;

    SNAP(test);
    SNAP(counter);
    SNAP(SheepTotal);

    GLUE(this is a, concatenated stuff);
}