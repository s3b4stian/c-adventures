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
    printf("string s9[%d][%d] [%s]\n", s9->len, s9->len_null, s9->string);
    string_t* s10 = string_substring(s9, -12, c);
    string_t* s11 = string_substring(s9, -11, c);
    string_t* s12 = string_substring(s9, -10, c);
    string_t* s13 = string_substring(s9, -9, c);
    string_t* s14 = string_substring(s9, -8, c);
    string_t* s15 = string_substring(s9, -7, c);
    string_t* s16 = string_substring(s9, -6, c);
    string_t* s17 = string_substring(s9, -5, c);
    string_t* s18 = string_substring(s9, -4, c);
    string_t* s19 = string_substring(s9, -3, c);
    string_t* s20 = string_substring(s9, -2, c);
    string_t* s21 = string_substring(s9, -1, c);
    string_t* s22 = string_substring(s9, 0, c);
    string_t* s23 = string_substring(s9, 1, c);
    string_t* s24 = string_substring(s9, 2, c);
    string_t* s25 = string_substring(s9, 3, c);
    string_t* s26 = string_substring(s9, 4, c);
    string_t* s27 = string_substring(s9, 5, c);
    string_t* s28 = string_substring(s9, 6, c);
    string_t* s29 = string_substring(s9, 7, c);
    string_t* s30 = string_substring(s9, 8, c);
    string_t* s31 = string_substring(s9, 9, c);
    string_t* s32 = string_substring(s9, 10, c);
    string_t* s33 = string_substring(s9, 11, c);
    string_t* s34 = string_substring(s9, 12, c);

    printf("string s10[%d][%d] [%s]\n", s10->len, s10->len_null, s10->string);
    printf("string s11[%d][%d] [%s]\n", s11->len, s11->len_null, s11->string);
    printf("string s12[%d][%d] [%s]\n", s12->len, s12->len_null, s12->string);
    printf("string s13[%d][%d] [%s]\n", s13->len, s13->len_null, s13->string);
    printf("string s14[%d][%d] [%s]\n", s14->len, s14->len_null, s14->string);
    printf("string s15[%d][%d] [%s]\n", s15->len, s15->len_null, s15->string);
    printf("string s16[%d][%d] [%s]\n", s16->len, s16->len_null, s16->string);
    printf("string s17[%d][%d] [%s]\n", s17->len, s17->len_null, s17->string);
    printf("string s18[%d][%d] [%s]\n", s18->len, s18->len_null, s18->string);
    printf("string s19[%d][%d] [%s]\n", s19->len, s19->len_null, s19->string);
    printf("string s20[%d][%d] [%s]\n", s20->len, s20->len_null, s20->string);
    printf("string s21[%d][%d] [%s]\n", s21->len, s21->len_null, s21->string);
    printf("string s22[%d][%d] [%s]\n", s23->len, s22->len_null, s22->string);
    printf("string s23[%d][%d] [%s]\n", s23->len, s23->len_null, s23->string);
    printf("string s24[%d][%d] [%s]\n", s24->len, s24->len_null, s24->string);
    printf("string s25[%d][%d] [%s]\n", s25->len, s25->len_null, s25->string);
    printf("string s26[%d][%d] [%s]\n", s26->len, s26->len_null, s26->string);
    printf("string s27[%d][%d] [%s]\n", s27->len, s27->len_null, s27->string);
    printf("string s28[%d][%d] [%s]\n", s28->len, s28->len_null, s28->string);
    printf("string s29[%d][%d] [%s]\n", s29->len, s29->len_null, s29->string);
    printf("string s30[%d][%d] [%s]\n", s30->len, s30->len_null, s30->string);
    printf("string s31[%d][%d] [%s]\n", s31->len, s31->len_null, s31->string);
    printf("string s32[%d][%d] [%s]\n", s32->len, s32->len_null, s32->string);
    printf("string s33[%d][%d] [%s]\n", s33->len, s33->len_null, s33->string);
    printf("string s34[%d][%d] [%s]\n", s34->len, s34->len_null, s34->string);

    string_delete(s9);
    string_delete(s10);
    string_delete(s11);
    string_delete(s12);
    string_delete(s13);
    string_delete(s14);
    string_delete(s15);
    string_delete(s16);
    string_delete(s17);
    string_delete(s18);
    string_delete(s19);
    string_delete(s20);
    string_delete(s21);
    string_delete(s22);
    string_delete(s23);
    string_delete(s24);
    string_delete(s25);
    string_delete(s26);
    string_delete(s27);
    string_delete(s28);
    string_delete(s29);
    string_delete(s30);
    string_delete(s31);
    string_delete(s32);
    string_delete(s33);
    string_delete(s34);

    //string_t* s40 = string_init("Hello Word, this is a very long string. Split it!");
    string_t* s40 = string_init("Hello Word ");

    printf("string s40[%d][%d] [%s]\n", s40->len, s40->len_null, s40->string);

    string_t_array* s41 = string_split(s40, " ,.!");

    //string_split(s40, " ,.!");

    //printf("[%d][%d]\n", s41->len, s41->len_mem);

    //for (size_t i = 0; i < s41->len; i++) {
    //    printf("[%s]", s41->strings[i]->string);
   // }

    //printf("\n");

    string_delete(s40);
    string_delete_stt_array(s41);

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