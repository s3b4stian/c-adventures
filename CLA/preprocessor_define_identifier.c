#include <stdio.h>

#define PI 3.1415

#define	SIZE 100
#define	SIZE2 4+4
#define	SIZE3 (4+4) //use always parentheses

//gcc -E preprocessor_define_identifier.c
//shows preprocessor result
int main(void) {
	
    //using identifier PI
    float s = 2 * PI * 10.0;
	

    //using identifier SIZE
    int arr[SIZE], i, sum = 0;

    for(i = 0; i < SIZE; i++)
        arr[i] = 2 * i;

    for(i = 0; i < SIZE; i++)
        sum += arr[i];

    printf("%d\n", sum);


    //using identifier SIZE2
    printf("%d\n", 2 * SIZE2); //expected 16 returned 12

    //using identifier SIZE3
    printf("%d\n", 2 * SIZE3); //expected 16 returned 16

    //other identifiers
    printf("%d\n",__LINE__);
    puts(__FILE__);
    puts(__DATE__);
    puts(__TIME__);
    printf("%d\n",__STDC__);
}