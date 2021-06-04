#include <string.h>
#include <stdio.h>

typedef struct {
    //string len
    int len;
    //string len + null byte
    //always len + 1
    int len_null;
    char *string;
} string_t;



string_t string_init(char* string)
{
    int len;
    for (len = 0; string[len] != '\0'; len++);

    return (string_t) {
        .len = len,
        .len_null = len + 1,
        .string = string
    };
}

string_t string_concat(char *_string, string_t first, string_t second)
{
    //get total len without null bytes
    int total_len = first.len + second.len;
    
    //copy first string
    for (int i = 0; i <= first.len; _string[i++] = first.string[i]); 
    //copy second string
    for (int i = 0; i < total_len; _string[first.len + i++] = second.string[i]);
    
    //set null byte at the end of the string
    _string[total_len] = '\0';

    return (string_t) {
        .len = total_len,
        .len_null = total_len + 1,
        .string = _string
    };
}

string_t string_copy(char *_string, string_t first)
{
    for (int i = 0; i <= first.len; _string[i++] = first.string[i]);

    return (string_t) {
        .len = first.len,
        .len_null = first.len + 1,
        .string = _string
    };
}

int main(void)
{
    string_t s1 = string_init("ciao ");
    printf("string s1[%d,%d]: %s\n", s1.len, s1.len_null, s1.string);

    string_t s2 = string_init("ciao");
    printf("string s2[%d,%d]: %s\n", s2.len, s2.len_null, s2.string);

    char buffer[s1.len + s2.len_null];
    string_t s3 = string_concat(buffer, s1, s2);

    printf("string s3[%d,%d]: %s\n", s3.len, s3.len_null, s3.string);
    //printf("string s3[%p]:\n", s3.string);

    char buffer1[s3.len_null];
    string_t s4 = string_copy(buffer1, s3);
    
    printf("string %p %p:\n", s3.string, s4.string);

    //s3.string = 'a';

    //memcpy(s3.string, "test", s3.len);

    printf("string %s -- %s:\n", s3.string, s4.string);

    return 0;
}