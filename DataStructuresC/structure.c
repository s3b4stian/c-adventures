#include <stdio.h>

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
    // declared
    // on stack
    struct rectangle a;

    // initialize rectangle a
    // length: 25
    // heigth: 15
    a.length = 25;
    a.height = 15;

    // rectangle b
    // declared and initialized
    // length: 20
    // height: 10
    // on stack
    struct rectangle b = {20, 10};

    // print rectangle areaS
    printf("Area of rectangle a{%d, %d} is: %d\n", a.length, a.height, a.length * a.height);
    printf("Area of rectangle b{%d, %d} is: %d\n", b.length, b.height, b.length * b.height);

    // define struct card rapresenting a card
    struct card {
        int face;
        int shape;
        int color;
    };

    // declaring a deck of cards
    struct card deck[52];

    // initializing the deck of cards
    int card = 0;

    // shape: 0 to 3 as hearts, diamonds, clubs, pades
    for (int shape = 0; shape < 4; shape++) {

        // face: 0 to 12 as A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K
        for (int face = 0; face < 13; face++) {

            deck[card].face = face;
            deck[card].shape = shape;

            // color
            // 0 for red, 1 for black
            if (shape > 1) {
                deck[card].color = 0;
            } else {
                deck[card].color = 1;
            }

            card++;
        }
    }

    // print all cards
    for (int i = 0; i < 52; i++) {
        
        printf("Card: face %d, shape %d, color %d\n", deck[i].face, deck[i].shape, deck[i].color);
    }
}
