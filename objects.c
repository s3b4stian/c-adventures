#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    unsigned char *name;
    unsigned char *surname;

    void (*get)(struct person *);
    void (*sayHello)(struct person *);
};

void getPerson(struct person *this)
{
    printf("%s %s\n", this->name, this->surname);
}

void sayHello(struct person *this)
{
    printf("%s %s say Hello Word\n", this->name, this->surname);
}

void person_get(struct person *this)
{
    printf("functional: %s %s\n", this->name, this->surname);
}

void person_say_hello(struct person *this)
{
    printf("functional: %s %s say Hello Word\n", this->name, this->surname);
}

struct person *person_init(char *name, char *surname)
{
    struct person *this = calloc(1, sizeof(struct person));
    //pointers to function
    this->get = &getPerson;
    this->sayHello = &sayHello;
    //struct properties
    this->name = calloc(strlen(name) + 8, sizeof(unsigned char));
    this->surname = calloc(strlen(surname) + 8, sizeof(unsigned char));
    
    strcpy(this->name, name);
    strcpy(this->surname, surname);
    
    return this;
}

void person_destroy(struct person *this)
{
    free(this->name);
    free(this->surname);

    free(this);
}

int main()
{
    struct person *me = person_init("Sebastian", "Rapetti");
    
    person_get(me);
    person_say_hello(me);

    me->get(me);
    me->sayHello(me);
    
    person_destroy(me);
    

    struct person *another = person_init("Another", "Person");
    
    person_get(another);
    person_say_hello(another);

    another->get(another);
    another->sayHello(another);
    
    person_destroy(another);
    
    return 0;
}
