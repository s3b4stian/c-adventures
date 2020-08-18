#include <stdio.h>
#include <stdlib.h>

/**
 * Sum two integers.
 * Parameters passed by value.
 * 
 * @param int a
 * @param int b
 * 
 * @return int
 */
int add (int a, int b) {

    int c;

    c = a + b;

    return c;
}

/**
 * Swap two integers.
 * Parameters passed by address.
 * 
 * @param int *a
 * @param int *b
 * 
 * @return void
 */
void swap (int *x, int *y)
{
    int temp;

    temp = *x;
    *x = *y;
    *y = temp;
}

/**
 * Print all values of an array.
 * Parameters passed by address.
 * 
 * @param int[] a
 * @param int   n
 * 
 * @return void
 */ 
void print_array(int a[], int n)
{
    printf("\nArray of %d elements\n", n);

    for (int i = 0; i < n; i++) {
        
        printf("a[%d]: %d\n", i, a[i]);
    }
}

/**
 * Allocate an array of n elements in heap.
 * 
 * @param int n
 * 
 * @return int *
 */ 
int * allocate_array(int n)
{
    int *p;

    p = (int *) malloc(n * sizeof(int));

    return p;
}

// define a structure rectangle
// with two properties
struct rectangle {
    int length;
    int height;
};

/**
 * Calculate the area of rectangle
 * Parameter passed by value
 * 
 * @param struct rectangle a
 * 
 * @return int
 */
int area_by_value(struct rectangle a)
{
    return a.length * a.length;
}

/**
 * Calculate the area of rectangle
 * Parameter passed by address
 * 
 * @param struct rectangle *a
 * 
 * @return int
 */
int area_by_address(struct rectangle *a)
{
    return a->length * a->length;
}

/**
 * Change the length of a rectangle
 * Parameter passed by address
 * 
 * @param struct rectangle *a
 * @param int    new_l
 * 
 * @return void
 */
void change_length(struct rectangle *a, int new_l)
{
    a->length = new_l;
}

/**
 * Main.
 */
int main () {

    // use of function
    // passing parameter by value
    int x, y, z;

    x = 10;
    y = 5;

    // call add passing x and y by value
    z = add(x, y);

    printf("Sum of %d + %d = %d\n", x, y, z);

    // use of function
    // passing parameters by address
    int a, b;

    a = 10;
    b = 20;

    printf("\nValue of a is %d and value of b is %d = %d\n", a, b);

    // call swap passing a and b as address
    swap(&a, &b);

    printf("After SWAP value of a is %d and value of b is %d = %d\n", a, b);

    // use of function
    // passing an array as parameter
    // array passed always by address
    int c[5] = {2, 4, 6, 8, 10};

    print_array(c, 5);

    // use of function
    // return pointer to array
    int *d;

    d = allocate_array(5);

    d[0] = 12;
    d[1] = 14;
    d[2] = 16;
    d[3] = 18;
    d[4] = 110;

    print_array(d, 5);

    free(d);

    // use function
    // passing a structure as parameters
    // paremeter passe by value

    struct rectangle r = {10, 5};

    int area_r = area_by_value(r);

    printf("\nArea of rectangle r{%d, %d} is: %d\n", r.length, r.height, area_r);

    // use function
    // passing a structure as parameters
    // paremeter passe by value
    struct rectangle s = {15, 10};

    int area_s = area_by_address(&s);

    printf("Area of rectangle s{%d, %d} is: %d\n", s.length, s.height, area_s);

    change_length(&s, 20);

    int area_s1 = area_by_address(&s);

    printf("New area of rectangle s{%d, %d} is: %d\n", s.length, s.height, area_s1);
}