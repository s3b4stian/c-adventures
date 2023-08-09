#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack_queue.h"

// concrete implementation
typedef struct _person
{
    char *name;
    int age;
} person, *p_person;

// allocate a person in heap
p_person get_person(char *name, size_t age)
{
    size_t len = strlen(name);

    p_person tmp = calloc(1, sizeof(person));
    tmp->name = calloc(len + 4, sizeof(char));
    tmp->age = age;

    memcpy(tmp->name, name, len);

    return tmp;
}

// deallocate a person
void free_person(p_person p)
{
    free(p->name);
    free(p);
}

void test_queue()
{
    p_abstract_list pq = get_list();

    p_person p1 = get_person("Hal", 25);
    p_person p2 = get_person("John", 30);
    p_person p3 = get_person("Jack", 42);
    p_person p4 = get_person("Marc", 33);
    p_person p5 = get_person("Kat", 28);

    push(pq, p1);
    push(pq, p2);
    push(pq, p3);
    push(pq, p4);
    push(pq, p5);

    printf("QUEUE \n");
    printf("%li elements \n\n", pq->elements);

    p_person p;
    while ((p = (p_person)poll(pq)))
    {
        printf("dequeue %s age %i\n", p->name, p->age);
        printf("%li elements in queue\n\n", pq->elements);
    }

    // poll nothing
    p = (p_person)poll(pq);
    p = (p_person)poll(pq);

    free(pq);

    free_person(p1);
    free_person(p2);
    free_person(p3);
    free_person(p4);
    free_person(p5);
}

void test_stack()
{
    p_abstract_list pq = get_list();

    p_person p1 = get_person("Hal", 25);
    p_person p2 = get_person("John", 30);
    p_person p3 = get_person("Jack", 42);
    p_person p4 = get_person("Marc", 33);
    p_person p5 = get_person("Kat", 28);

    push(pq, p1);
    push(pq, p2);
    push(pq, p3);
    push(pq, p4);
    push(pq, p5);

    printf("STACK \n");
    printf("%li elements \n\n", pq->elements);

    p_person p;
    while ((p = (p_person)pop(pq)))
    {
        printf("pop %s age %i\n", p->name, p->age);
        printf("%li elements in stack\n\n", pq->elements);
    }

    // pop nothing
    p = (p_person)pop(pq);
    p = (p_person)pop(pq);

    free(pq);

    free_person(p1);
    free_person(p2);
    free_person(p3);
    free_person(p4);
    free_person(p5);
}

int main()
{

    test_queue();

    test_stack();

    return 0;
}