#include <stdio.h>

#include "strings_t.h"

//compile: gcc test.c strings_t.c
int main(void)
{
    string_t s1 = string_init("Hello ");
    printf("string_init s1[%d][%d] [%s]\n", s1.len, s1.len_null, s1.string);

    string_t s2 = string_init("Word");
    printf("string_init s2[%d][%d] [%s]\n", s2.len, s2.len_null, s2.string);

    //macro expand to
    //char s3_buffer[s1.len + s2.len_null];
    //string_t s3 = string_concat(s3_buffer, s1, s2);
    STRING_CONCAT(s3, s1, s2);
    printf("string_concat s3[%d][%d] [%s]\n", s3.len, s3.len_null, s3.string);
    
    //macro expand to
    //char s4_buffer[s3.len_null];
    //string_t s4 = string_copy(s4_buffer, s3);
    STRING_COPY(s4, s3);
    printf("string_copy s3[%s] s4[%s]\n", s3.string, s4.string);

    string_t s5 = string_init("  \tWord  ");
    //macro expand to
    //char s6_buffer[s5.len_null];
    //string_t s6 = string_trim_left(s6_buffer, s5, " \t");
    STRING_TRIM_LEFT(s6, s5, " \t");
    printf("string_trim_left s5[%d][%d] [%s]\n", s5.len, s5.len_null, s5.string);
    printf("string_trim_left s6[%d][%d] [%s]\n", s6.len, s6.len_null, s6.string);

    //macro expand to
    //char s7_buffer[s6.len_null];
    //string_t s7 = string_trim_right(s7_buffer, s6, " \n");
    STRING_TRIM_RIGHT(s7, s6, " \n");
    printf("string_trim_right s6[%d][%d] [%s]\n", s6.len, s6.len_null, s6.string);
    printf("string_trim_right s7[%d][%d] [%s]\n", s7.len, s7.len_null, s7.string);

    //macro expand to
    //s7.len = 0;
    //s7.len_null = 0;
    //string_zero(s7);
    STRING_ZERO(s7);
    printf("string_zero s7[%d][%d] [%s]\n", s7.len, s7.len_null, s7.string);

    return 0;
}