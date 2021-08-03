#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
    //structuri with flexible member
    // - the array must be the last member of the structure;
    // - there may be only one such array inside the structure (this can be assumed from the previous limitation, of course)
    struct vararr {
        int no;
        float vals[];
    };

    //allocate memory for the structure and for the flexible array
    int size = 10;
    struct vararr* va = malloc(sizeof(struct vararr) + size * sizeof(int));
    va->no = size;
    
    //fill the array
    for (int i = 0; i < size; i++)
        va->vals[i] = i;
    
    printf("%ld\n", sizeof( * va));
   
    free(va);

    return 0;
}