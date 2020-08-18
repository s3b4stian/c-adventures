#include <stdio.h>
#include <stdlib.h>

/**
 * Main.
 */
int main () {

    // define a structure rectangle
    // with two properties
    struct rectangle {
        int length;
        int height;
    };

    // rectangle a
    // declared and initialized
    // on stack
    struct rectangle a = {15, 10};

    // pointer to rectangle a
    struct rectangle *b = &a;

    // access to rectangle a through pointer b
    (*b).length = 20;

    // access to rectangle a through pointer b
    // using simple syntax
    b->length = 25;

    // pointer to rectangle c
    // declared
    // on stack
    struct rectangle *c;

    // allocate heap memory for one rectangle struct
    // type casting required becaouse malloc return pointer to void
    c = (struct rectangle *) malloc(sizeof(struct rectangle));

    // initialize rectangle c
    c->length = 10;
    c->height = 5;
}