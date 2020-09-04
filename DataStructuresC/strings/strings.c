#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Main.
 */
int main () {

    char tmp;

    tmp = 'A';

    printf("%c\n", tmp);

    // array of characters
    // initializing methods

    // first method
    char tmp1[5] = {'A', 'B', 'C', 'D', 'E'};
    // second method
    char tmp2[] = {'A', 'B', 'C', 'D', 'E'};
    // third method
    char tmp3[] = {65, 66, 67, 68, 69};

    // content: A B 0 0 0
    char tmp4[5] = {'A', 'B'};

    // array of chars
    // with \0 become a string
    // \0 is
    // string delimiter
    // or null char
    // or string terminator

    // first method
    char name[10] = {'S', 'e', 'b', 'a', '\0'};
    // second method
    char name1[] = {'S', 'e', 'b', 'a', '\0'};
    // third method
    char name2[] = "Seba1";
    // fourth method
    // poiter to a string
    // string stored in read only part of data segment
    // no need free
    // dangerous best use 
    // const char *name3 = "SebaPointer\0";
    char *name3 = "SebaPointer\0";

    // this work
    name3 = "SebaPointerReAssignated\0";
    printf("%s: %x\n", name3, &name3);
    
    // this not work, try to modify read only memory
    //*(name3+0) = 's';
    //name3[0] = 's';


    // fifth method
    // poiter to a string
    // string stored in heap
    char *name4 = (char *) malloc(32 * sizeof(char));
    // for initialize
    strcpy(name4, "SebaPointerToHeap");
    // or 
    memcpy(name4, "SebaPointerToHeap", 18);
    // this not work
    //name4 = "SebaPointerToHeap\0";

    printf("%s: %x\n", name4, &name4);

    // valid
    name4[0] = 's';
    name4[4] = 'p';
    name4[11] = 't';
    name4[13] = 'h';

    printf("%s\n", name);
    printf("%s\n", name1);
    printf("%s\n", name2);
    printf("%s: %x\n", name3, &name3);
    printf("%s: %x\n", name4, &name4);

    // find length of a string
    printf("Length of %s is: %d\n", name, strlen(name));
    printf("Length of %s is: %d\n", name1, strlen(name1));
    printf("Length of %s is: %d\n", name2, strlen(name2));
    printf("Length of %s is: %d\n", name3, strlen(name3));
    printf("Length of %s is: %d\n", name4, strlen(name4));

    // find length of a string
    int i;
    for (i = 0; name3[i] != '\0'; i++);
    printf("(Custom method) Length of %s is: %d\n", name3, i);

    // change the case of a string to lowercase
    for (i = 0; name2[i] != '\0'; i++){
        
        if (name2[i] >= 65 && name2[i] <= 90) {
            name2[i] = name2[i] + 32;
        }
        
    }

    printf("Lowercase %s\n", name2);

    // change the case of a string to uppercase
    for (i = 0; name2[i] != '\0'; i++){
        
        if (name2[i] >= 97 && name2[i] <= 122) {
            name2[i] = name2[i] - 32;
        }
        
    }

    printf("Uppercase %s\n", name2);

    free(name4);
}
