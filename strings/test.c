#include <stdio.h>

#include "strings_t.h"

//compile: gcc test.c strings_t.c
int main(void)
{
    string_t s1 = string_init("Hello ");
    printf("string_init s1[%d] [%d] [%s]\n", s1.len, s1.len_null, s1.string);

    string_t s2 = string_init("Word");
    printf("string_init s2[%d] [%d] [%s]\n", s2.len, s2.len_null, s2.string);

    //char buffer[s1.len + s2.len_null];
    //string_t s3 = string_concat(buffer, s1, s2);
    STRING_CONCAT(s3, s1, s2);
    printf("string_concat s3[%d] [%d] [%s]\n", s3.len, s3.len_null, s3.string);
    

    //char buffer1[s3.len_null];
    //string_t s4 = string_copy(buffer1, s3);
    STRING_COPY(s4, s3);
    printf("string_copy [%s] [%s]\n", s3.string, s4.string);


    string_t s5 = string_init("  \tWord");

    //char buffer1[s5.len_null];
    //string_t s6 = string_trim_left(buffer1, s5, " ");
    STRING_TRIM_LEFT(s6, s5, " \t");
    printf("string_trim_left s2[%d] [%d] [%s]\n", s5.len, s5.len_null, s5.string);
    printf("string_trim_left s2[%d] [%d] [%s]\n", s6.len, s6.len_null, s6.string);

    return 0;
}