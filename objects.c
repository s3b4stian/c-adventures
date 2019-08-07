#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    unsigned char *name;
    unsigned char *surname;
    void (*construct)(struct person *, char *, char *);
    void (*get)(struct person *);
    void (*sayHello)(struct person *);
};

void construct(struct person *this, char *name, char *surname)
{
    this->name = calloc(strlen(name) + 8, sizeof(unsigned char));
    this->surname = calloc(strlen(surname) + 8, sizeof(unsigned char));
    
    strcpy(this->name, name);
    strcpy(this->surname, surname);
}

void getPerson(struct person *this)
{
    printf("%s %s\n", this->name, this->surname);
}

void sayHello(struct person *this)
{
    printf("%s %s say Hello Word\n", this->name, this->surname);
}

struct person *createInstanceOfPerson(char *name, char *surname)
{
    struct person *this = calloc(1, sizeof(struct person));
    this->construct = &construct;
    this->get = &getPerson;
    this->sayHello = &sayHello;
    
    this->construct(this, name, surname);
    
    return this;
}

void destroyInstanceOfPerson(struct person *this)
{
    free(this->name);
    free(this->surname);

    free(this);
}

int main()
{
    struct person *me = createInstanceOfPerson("Sebastian", "Rapetti");
    
    me->get(me);
    me->sayHello(me);
    
    destroyInstanceOfPerson(me);
    
    struct person *another = createInstanceOfPerson("Another", "Persona");
    
    another->get(another);
    another->sayHello(another);
    
    destroyInstanceOfPerson(another);
    
    return 0;
}
