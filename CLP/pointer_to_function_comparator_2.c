#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[10];
    int age;
}
person_t;

person_t * person_init(char *name, int age) {
    person_t * new = malloc(sizeof(person_t));
    strcpy(new -> name, name);
    new -> age = age;
    return new;
}

void print(person_t **base, person_t **found) {
    if (found)
        printf("[%ld](%s, %d)\n", found - base, ( * found) -> name, ( * found) -> age);
    else
        printf("(null)\n");
}

int cmp(const void* v1, const void* v2) {
    //casting to v1 pointer to pointer to person_t then dereferentiate
    //same v2
    return strcmp((*(person_t**)v1)->name, (*(person_t**)v2)->name);
}

int main(void) {
    
    person_t* pp[] = {
        person_init("Charlie", 23),
        person_init("Foxtrot", 40),
        person_init("Hotel", 15),
        person_init("Julliet", 9)
    };
    
    person_t key, *pkey = &key;

    strcpy(key.name, "Hotel");
    print(pp, bsearch(&pkey, pp, 4, sizeof(person_t*), cmp));

    strcpy(key.name, "Quebec");
    print(pp, bsearch(&pkey, pp, 4, sizeof(person_t*), cmp));

    strcpy(key.name, "Charlie");
    print(pp, bsearch(&pkey, pp, 4, sizeof(person_t*), cmp));

    int i;
    for (i = 0; i < 4; i++)
        free(pp[i]);
    
    return 0;
}