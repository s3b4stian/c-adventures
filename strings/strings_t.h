#ifndef _STRINGS_T_H
#define _STRINGS_T_H 1


//copy S2 to S1
#define STRING_COPY(S1, S2)                    \
    char S1##_buffer[S2.len_null];             \
    string_t S1 = string_copy(S1##_buffer, S2) \

//concat S1 to S2 and put result in S2
#define STRING_CONCAT(S3, S1, S2)                    \
    char S3##_buffer[S1.len + S2.len_null];          \
    string_t S3 = string_concat(S3##_buffer, S1, S2) \

//trim left string S1 considering chars in S2 and put result in S3
#define STRING_TRIM_LEFT(S3, S1, S2)                     \
    char S3##_buffer1[S1.len_null];                      \
    string_t S3 = string_trim_left(S3##_buffer1, S1, S2) \

//trim right string S1 considering chars in S2 and put result in S3
#define STRING_TRIM_RIGHT(S3, S1, S2)                     \
    char S3##_buffer1[S1.len_null];                       \
    string_t S3 = string_trim_right(S3##_buffer1, S1, S2) \

//fill S1 string with null chars
#define STRING_ZERO(S1) \
    S1.len = 0;         \
    S1.len_null = 0;    \
    string_zero(S1)     \

//string struct
typedef struct {
    //string len
    int len;
    //string len + null byte
    //always len + 1
    int len_null;
    char *string;
} string_t;


string_t string_init(char string[]);


string_t string_concat(char _string[], string_t first, string_t second);


string_t string_copy(char _string[], string_t first);


string_t string_trim_left(char _string[], string_t first, char chars[]);


string_t string_trim_right(char _string[], string_t first, char chars[]);


void string_zero(string_t first);

#endif