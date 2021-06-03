#include <stdio.h>
#include <stdlib.h>

/**
 * Main.
 */
int main () {

    //a string of 5 chars, 4 + null byte
    char word[10] = "dump";
    printf("word[10]:  %s\n", word);

    //update the second element of the array
    //used single quotes because is only a single char
    word[1] = 'a';
    puts("word[1] = 'a';");
    printf("word[10]:  %s\n", word);

    //word is an array, it is possible to access elements using pointer notation
    printf("word[0]:  %c\n", word[0]);
    printf("word[1]:  %c\n", word[1]);
    printf("word[2]:  %c\n", word[2]);
    printf("word[3]:  %c\n", word[3]);

    printf("*(word):      %c\n", *(word));
    printf("*(word + 1):  %c\n", *(word + 1));
    printf("*(word + 2):  %c\n", *(word + 2));
    printf("*(word + 3):  %c\n", *(word + 3));

    //[] operator is commutative
    printf("word[0]:  %c\n", word[0]);
    printf("0[word]:  %c\n", 0[word]);

    //another example
    char string[] = "ABC";
    char *p;
    char c;

    //assign the second element of the string
    p = string + 1;
    printf("p = string + 1:  %c\n", *p);
    //assign the second element of the string
    //still valid but less elegant
    p = &string[1];
    printf("p = &string[1]:  %c\n", *p);

    //assign to c the value of poiter p
    //then increment the pointer
    //equal to
    //c = (*p)++;
    //or
    //c = *p; p++;
    c = *p++;
    printf("c = *p++:  %c\n", c);
    printf("p:  %c\n", *p);

    //last element of the array
    p = string + 2;
    printf("p = string + 2:  %c\n", *p);
    //assign new value to the last - 1 element of the array
    p[-1] = 'D';
    printf("p[-1] = 'D':  %c\n", *(--p));
    printf("string:  %s\n", string);

    //same but with different syntax
    p = string + 2;
    *(p - 1) = 'E';
    printf("*(p - 1) = 'E':  %c\n", *(--p));
    printf("string:  %s\n", string);

}