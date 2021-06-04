#ifndef _STRINGS_T_H
#define _STRINGS_T_H 1

//#define CONCAT(a, b) CONCAT_INNER(a, b)
//#define CONCAT_INNER(a, b) a ## b

//#define UNIQUE_NAME(base) CONCAT(base, __COUNTER__)

#define PASTE_HELPER(a,b) a ## b
#define PASTE(a,b) PASTE_HELPER(a,b)

//copy S2 to S1
#define STRING_COPY(S1, S2)                    \
    char S1##_buffer[S2.len_null];             \
    string_t S1 = string_copy(S1##_buffer, S2) \

//concat S1 to S2 and put result in S2
#define STRING_CONCAT(S3, S1, S2)                             \
    char S3##_buffer[S1.len + S2.len_null];          \
    string_t S3 = string_concat(S3##_buffer, S1, S2) \

//trim left string S1 considering chars in S2 and put result in S3
#define STRING_TRIM_LEFT(S3, S1, S2)                              \
    char S3##_buffer1[S1.len_null];                      \
    string_t S3 = string_trim_left(S3##_buffer1, S1, S2) \

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


#endif