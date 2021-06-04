#include <stdio.h>
#include <stdlib.h>

struct date {
    int year;
    int month;
    int day;
};

struct student {
    char  name[26];
    float time;
    int   recent_chapter;
    struct date last_visit;
};

/**
 * Main.
 */
int main () {
    
    //declaring and initializing a variable struct student
    struct student he = {
        .name = "Sebastian",
        .time = 3.5,
        .recent_chapter = 4,
        .last_visit = {
            .year = 2021,
            .month = 10,
            .day = 24
        }
    };

    //declaring and initializing another variable struct student
    struct student she = {
        .name = "Antonella",
        .time = 3.5,
        .recent_chapter = 5,
        .last_visit = {
            .year = 2020,
            .month = 1,
            .day = 14
        }
    };

    struct student *other =  malloc(sizeof(struct student));
    
    *other = (struct student) {
        .name = "Other",
        .time = 1.5,
        .recent_chapter = 1,
        .last_visit = {
            .year = 2019,
            .month = 12,
            .day = 31
        }
    };

    //printing structures 
    printf("name: %s\n", he.name);
    printf("year: %d\n", he.last_visit.year);
    printf("name: %s\n", she.name);

    //printing pointer to structure
    printf("name: %s\n", other->name);
    printf("year: %d\n", other->last_visit.year);
    //printing pointer to structure using dereferencing
    printf("name: %s\n", (*other).name);

    free(other);
}