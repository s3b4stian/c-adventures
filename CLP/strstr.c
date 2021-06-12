#include <string.h>
#include <stdio.h>

void print(char * s, char * p) {
    if (p == NULL)
        printf("(null)\n");
    else
        printf("+%ld\n", p - s);
}

int main(void) {
    char * rhyme = "They all ran after the farmer's wife,"
    "Who cut off their tails with a carving knife,"
    "Did you ever see such a sight in your life,";
    
    char * p = strstr(rhyme, "all");
    
    while (p) {
        print(rhyme, p);
        p = strstr(p + 1, "all");
    }
    
    return 0;
}