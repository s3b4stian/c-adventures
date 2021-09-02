#include <string.h>
#include <stdio.h>

void print (char *s, char *p)
{
    if (p == NULL)
        printf ("(null)\n");
    else
        printf ("[%ld]\n", p - s);
}

int main (void)
{
    //search for the first occurence of the passed char
    char *str = "Mary had a little lamb";
    print (str, strchr(str, 'c'));
    print (str, strchr(str, 'a'));
    
    //same but starting from the end of the string
    //right to left
    char *str1 = "Mary had a little lamb";
    print (str1, strchr(str1, 'c'));
    print (str1, strchr(str1, 'a'));

    //search for all occurences of the char
    char *str2 = "Mary had a little lamb";
    char *p = strchr(str2, 'a');
    while (p) {
        print (str2, p);
        p = strchr(p + 1, 'a');
    }

    return 0;
}