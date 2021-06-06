#ifndef _STRINGS_T_H
#define _STRINGS_T_H 1

//string init
#define string_init(S1)                        \
    string_init_c(malloc(sizeof(string_t)), S1);

//string concat
#define string_concat(S1, S2) _Generic(         \
    (S1, S2),                                   \
    string_t*: string_concat_st,                \
    char*: string_concat_c                      \
)((S1), (S2))

//copy S2 to S1
//#define STRING_COPY(S1, S2)                    \
//    char S1##_buffer[S2.len_null];             \
//    string_t S1 = string_copy(S1##_buffer, S2)

//concat S1 to S2 and put result in S2
//#define STRING_CONCAT(S3, S1, S2)                    \
//    char S3##_buffer[S1.len + S2.len_null];          \
//    string_t S3 = string_concat(S3##_buffer, S1, S2)

//trim left string S1 considering chars in S2 and put result in S3
//#define STRING_TRIM_LEFT(S3, S1, S2)                    \
//    char S3##_buffer[S1.len_null];                      \
//    string_t S3 = string_trim_left(S3##_buffer, S1, S2)

//trim right string S1 considering chars in S2 and put result in S3
//#define STRING_TRIM_RIGHT(S3, S1, S2)                    \
//    char S3##_buffer[S1.len_null];                       \
//    string_t S3 = string_trim_right(S3##_buffer, S1, S2)

//creat a substring from S1 from S to E position and put result in S3
//#define STRING_SUBSTRING(S3, S1, S, E)                    \
//    char S3##_buffer[S1.len_null];                        \
//    string_t S3 = string_substring(S3##_buffer, S1, S, E)

//fill S1 string with null chars
//#define STRING_ZERO(S1) \
//    S1.len = 0;         \
//    S1.len_null = 0;    \
//    string_zero(S1)

//string struct
typedef struct {
    //string len
    int len;
    //string len + null byte
    //always len + 1
    int len_null;
    char *string;
} string_t;


//init
//first argument is the result of malloc(sizeof(string_t)) 
string_t* string_init_c(string_t* _string, char string[]);

//concat to new string
string_t* string_concat_to_new(string_t* first, string_t* second);

//cancat to first string
int string_concat_c(string_t* first, char* second);
int string_concat_st(string_t* first, string_t* second);

//string copy
string_t* string_copy(string_t* first);


//string_t string_trim_left(char _string[], string_t first, char chars[]);


//string_t string_trim_right(char _string[], string_t first, char chars[]);


//string_t string_substring(char _string[], string_t first, int from, int to);


void string_delete(string_t* _string);

#endif