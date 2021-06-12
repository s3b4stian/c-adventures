#include <string.h>
#include <stdio.h>

int main(void) {
    
    //don't use char *hamlet = "abc"
    //this because a *hamlet is read only 
    //strtok to tokenize the string replace delimiter chars with null bytes
    char hamlet[] = "To be, or not to be: that is the question:\n"
    "Whether 'tis nobler in the mind to suffer\n"
    "The slings and arrows of outrageous fortune,\n"
    "Or to take arms against a sea of troubles,\n"
    "And by opposing end them?";
    char * delim = ",:? \n";
    char * token = strtok(hamlet, delim);
    
    while (token) {
        printf("%s ", token);
        token = strtok(NULL, delim);
    }
   
    printf("\n");
    return 0;
}