#include <stdio.h>
#include <stdlib.h>
#include "strings_t.h"

//compile: gcc test.c strings_t.c
//valgrind: valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./a.out
int main(void)
{
    //init macro
    string_t* s1 = string_init("Hello");
    printf("string_init s1[%d][%d] [%s]\n", s1->len, s1->len_null, s1->string);

    //init macro
    string_t* s2 = string_init(" Word");
    printf("string_init s2[%d][%d] [%s]\n", s2->len, s2->len_null, s2->string);

    //copy function
    string_t* s1tmp = string_copy(s1);
    string_t* s2tmp = string_copy(s2);

    string_delete(s1tmp);
    string_delete(s2tmp);

    //concat macro, generic
    int result = string_concat(s1, s2);
    result = string_concat(s1, s2);
    result = string_concat(s1, s2);
    result = string_concat(s1, s2);
    result = string_concat(s1, s2);
    result = string_concat(s1, " Word");
    result = string_concat(s1, " Word");
    result = string_concat(s1, " Word");
    printf("realloc[%d]\n", result);
    printf("string_init s1[%d][%d] [%s]\n", s1->len, s1->len_null, s1->string);

    //cancat new function
    string_t* s3 = string_concat_to_new(s1, s2);
    printf("string s1[%d][%d] [%s]\n", s1->len, s1->len_null, s1->string);
    printf("string s2[%d][%d] [%s]\n", s2->len, s2->len_null, s2->string);
    printf("string_concat_to_new s3[%d][%d] [%s]\n", s3->len, s3->len_null, s3->string);

    string_t* s4 = string_copy(s3);

    //delete function
    string_delete(s1);
    string_delete(s2);
    string_delete(s3);

    printf("string_copy s4[%d][%d] [%s]\n", s4->len, s4->len_null, s4->string);

    string_delete(s4);


    string_t* s5 = string_init(" \t \n \t Word   ");
    printf("string s5[%d][%d] [%s]\n", s5->len, s5->len_null, s5->string);

    result = string_trim_left(s5, " \t\n");
    printf("result[%d]\n", result);
    printf("string_trim_left s5[%d][%d] [%s]\n", s5->len, s5->len_null, s5->string);

    result = string_trim_right(s5, " \t\n");
    printf("result[%d]\n", result);
    printf("string_trim_right s5[%d][%d] [%s]\n", s5->len, s5->len_null, s5->string);

    string_delete(s5);


    string_t* s6 = string_init("   Word   ");
    string_t* s7 = string_trim_left_to_new(s6, " ");
    string_t* s8 = string_trim_right_to_new(s6, " ");
    
    printf("string s6[%d][%d] [%s]\n", s6->len, s6->len_null, s6->string);
    printf("string_trim_left_to_new s7[%d][%d] [%s]\n", s7->len, s7->len_null, s7->string);
    printf("string_trim_right_to_new s8[%d][%d] [%s]\n", s8->len, s8->len_null, s8->string);
    
    string_delete(s6);
    string_delete(s7);
    string_delete(s8);

    size_t c = 4;

    string_t* s9 = string_init("Hello Word");
    string_t* s10 = string_substring(s9, 0, c);
    string_t* s11 = string_substring(s9, -1, c);
    string_t* s12 = string_substring(s9, -2, c);
    string_t* s14 = string_substring(s9, -3, c);
    string_t* s15 = string_substring(s9, -4, c);
    string_t* s16 = string_substring(s9, -5, c);
    string_t* s17 = string_substring(s9, -6, c);
    string_t* s18 = string_substring(s9, -7, c);
    string_t* s19 = string_substring(s9, -8, c);
    string_t* s20 = string_substring(s9, -9, c);
    string_t* s21 = string_substring(s9, -10, c);
    string_t* s22 = string_substring(s9, -11, c);

    //macro expand to
    //char s6_buffer[s5.len_null];
    //string_t s6 = string_trim_left(s6_buffer, s5, " \t");
    //STRING_TRIM_LEFT(s6, s5, " \t");
    //printf("result[%d]\n", result);
    //printf("string_trim_left s5[%d][%d] [%s]\n", s5->len, s5->len_null, s5->string);
    //printf("string_trim_left s6[%d][%d] [%s]\n", s6.len, s6.len_null, s6.string);

    //macro expand to
    //char s7_buffer[s6.len_null];
    //string_t s7 = string_trim_right(s7_buffer, s6, " \n");
    //STRING_TRIM_RIGHT(s7, s6, " \n");
    //printf("string_trim_right s6[%d][%d] [%s]\n", s6.len, s6.len_null, s6.string);
    //printf("string_trim_right s7[%d][%d] [%s]\n", s7.len, s7.len_null, s7.string);

    //macro expand to
    //s7.len = 0;
    //s7.len_null = 0;
    //string_zero(s7);
    //STRING_ZERO(s7);
    //printf("string_zero s7[%d][%d] [%s]\n", s7.len, s7.len_null, s7.string);


    //string_t s9 = string_init("abcdef");
    //printf("string_init s9[%d][%d] [%s]\n", s9.len, s9.len_null, s9.string);
    //macro expand to
    //char s8_buffer[s4.len_null];
    //string_t s8 = string_substring(s8_buffer, s9, 2, 2);
    //STRING_SUBSTRING(s8, s9, 2, 2);
    //printf("string_substring(s9, 2, 2) s8[%d][%d] [%s]\n", s8.len, s8.len_null, s8.string);

    return 0;
}