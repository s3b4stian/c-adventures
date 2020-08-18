#include <stdio.h>
// #include <stdlib.h>

// define a structure rectangle
// with two properties
struct rectangle {
    int length;
    int height;

    int (*area_by_address)(struct rectangle *);
    void (*change_length)(struct rectangle *, int);
    void (*change_height)(struct rectangle *, int);
};

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
 * Change the height of a rectangle
 * Parameter passed by address
 * 
 * @param struct rectangle *a
 * @param int    new_l
 * 
 * @return void
 */
void change_height(struct rectangle *a, int new_h)
{
    a->height = new_h;
}

/**
 * Initialize a rectangle structure. 
 * 
 * @param struct rectangle *a
 * @param int    l
 * @param int    h
 * 
 * @return void
 */ 
void rectangle(struct rectangle *a, int l, int h)
{
    // link functions as method to rectangle
    a->area_by_address = &area_by_address;
    a->change_length = &change_length;
    a->change_height = &change_height;

    // assign values to properties
    a->length = l;
    a->height = h;
}

/**
 * Main.
 */
int main () {

    struct rectangle r;
    
    rectangle(&r, 20, 10);

    int area_r = r.area_by_address(&r);

    printf("\nArea of rectangle r{%d, %d} is: %d\n", r.length, r.height, area_r);

    r.change_length(&r, 25);
    r.change_height(&r, 15);

    int area_r1 = r.area_by_address(&r);

    printf("\nArea of rectangle r{%d, %d} is: %d\n", r.length, r.height, area_r1);
}