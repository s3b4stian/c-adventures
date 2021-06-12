#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_float(const void* v1, const void* v2) {

    float vv1 = * ((float*) v1);
    float vv2 = * ((float*) v2);
    
    if (vv1 > vv2)
        return 2;
    if (vv2 > vv1)
        return -2;
    
    return 0;
}

int cmp_int(const void* v1, const void* v2) {

    //meanings
    //((int*) v1) is casting the v1 as pointer to int
    //* in fron t of is deferencing the pointer
    //take the value of casted to pointer to int v1
    int vv1 = * ((int*) v1);
    int vv2 = * ((int*) v2);
    
    //shorter way
    //if result is 0 values euqals
    //if result greater than zero vv1 is greater than vv2
    //if result lower than zero vv1 is lower than vv2
    return vv1 - vv2;
    //shorter way other form
    //directly return the value without intermediate variables
    //return *((int*) v1) - *((int*) v2)

    //longer way
    //if (vv1 > vv2)
    //    return 1;
    //if (vv2 > vv1)
    //    return -1;
    
    //return 0;
}

typedef struct
{
  char name[10];
  int age;
} person_t;

person_t * person_init(char * name, int age) {
    //allocate memory
    person_t * new = malloc(sizeof(person_t));
    //populate struct
    strcpy(new->name, name);
    new->age = age;

    return new;
}

int person_t_cmp_age(const void* v1, const void* v2)
{
    return ((person_t *) v1)->age - ((person_t *) v2)->age;
}

int person_t_cmp_name(const void* v1, const void* v2)
{
    return strcmp(((person_t*) v1)->name, ((person_t*) v2)->name);
}

int person_t_cmp_all(const void* v1, const void* v2)
{
    //compare the name
    int res = strcmp(( * (person_t ** ) v1) -> name, ( * (person_t ** ) v2) -> name);
    
    //if the name is equal, compare the age
    if (res == 0)
        res = ( * (person_t ** ) v1) -> age - ( * (person_t ** ) v2) -> age;
    
    return res;
}

int main(void) {
    
    //sorting numbers
    float t_f[] = {3., 1., 5., 4., 2., 10., 15., 7., 33., 0., 8.};
    int t_i[] = {3, 1, 5, 4, 2, 10, 15, 7, 33, 0, 8};

    qsort(t_f, 11, sizeof(t_f[0]), cmp_float);
    
    for (int i = 0; i < 11; i++) {
        printf("%.2f; ", t_f[i]);
    }
    printf("\n");
    
    qsort(t_i, 11, sizeof(t_i[0]), cmp_int);
    
    for (int i = 0; i < 11; i++) {
        printf("%d; ", t_i[i]);
    }
    printf("\n");

    //binary search
    int key = 15;
    int* result = (int*) bsearch (&key, t_i, sizeof(t_i) / sizeof(t_i[0]), sizeof(t_i[0]), cmp_int);
    if (result) {
        printf("Searched value [%d] is at position [%ld]\n", key, result - t_i);
    }
    else {
        printf("Searched value [%d] not found\n", key);
    }

    //sorting a structure
    person_t pp[] = {
        {.name = "Zulu",   .age = 23},
        {.name = "Sierra", .age = 40},
        {.name = "Bravo",  .age = 15},
        {.name = "Lima",   .age = 9},
        {.name = "Hotel",   .age = 55},
        {.name = "Kilo",   .age = 30},
        {.name = "Echo",   .age = 35}
    };

    qsort (pp, sizeof (pp) / sizeof (person_t), sizeof (person_t), person_t_cmp_name);
    printf ("Sort by name\n");
    for (int i = 0; i < sizeof(pp) / sizeof (person_t); i++) {
        printf ("(%s, %d)\n", pp[i].name, pp[i].age);
    }

    qsort (pp, sizeof (pp) / sizeof (person_t), sizeof (person_t), person_t_cmp_age);
    printf ("Sort by age\n");
    for (int i = 0; i < sizeof(pp) / sizeof (person_t); i++) {
        printf ("(%s, %d)\n", pp[i].name, pp[i].age);
    }
    
    //binary search in a struct
    //same for name
    person_t key_a;
    key_a.age = 9;
    person_t* result_p = (person_t*) bsearch (&key_a, pp, sizeof(pp) / sizeof(pp[0]), sizeof(pp[0]), person_t_cmp_age);

    if (result_p) {
        printf("Searched value [%d] is at position [%ld](%s, %d)\n", key_a.age, result_p - pp, result_p->name, result_p->age);
    }
    else {
        printf("Searched value [%d] not found\n", key_a.age);
    }

    //sorting a structure using more than one criteria
    person_t * pp1[] = {
        person_init("Delta", 23),
        person_init("Victor", 40),
        person_init("Victor", 15),
        person_init("Delta", 9)
    };

    qsort(pp1, sizeof(pp1) / sizeof(person_t *), sizeof(person_t *), person_t_cmp_all);
    printf ("Sort by all properties\n");
    for (int i = 0; i < sizeof(pp1) / sizeof(person_t*); i++) {
        printf("(%s, %d)\n", pp1[i]->name, pp1[i]->age);
        
        free(pp1[i]);
    }

    

    return 0;
}