#ifndef _STRINGS_T_H
#define _STRINGS_T_H 1


//string init
#define string_init(S1)                             \
    string_init_from_char(malloc(sizeof(string_t)), S1);

//string concat generic
#define string_concat(S1, S2) _Generic((S1, S2), \
    string_t*: string_concat_stt,                \
    char*: string_concat_char                    \
)((S1), (S2))

//string delete
#define string_delete(S1) _Generic((S1),     \
    string_t*: string_delete_stt,            \
    string_t_array*: string_delete_stt_array \
)(S1)


//string struct
typedef struct {
    //string len
    size_t len;
    //string len + null byte
    //always len + 1
    size_t len_null;
    char *string;
} string_t;
//array of strings structs
typedef struct {
    size_t len;
    string_t** strings;
} string_t_array;


//init
//first argument is the result of malloc(sizeof(string_t))
//from_void allocate only memory and fills with nullbytes
string_t* string_init_from_void(string_t* _string, size_t len);
string_t* string_init_from_char(string_t* _string, char string[]);


//concat to new string
string_t* string_concat_to_new(string_t* first, string_t* second);


//cancat to first string
//stt is string_t
//return the length of the new string, -1 if fails
int string_concat_char(string_t* first, char* second);
int string_concat_stt(string_t* first, string_t* second);


//string copy
string_t* string_copy(string_t* first);


//trim a string, left side
//return value int, is the number of chars trimmed
int string_trim_left(string_t* first, char chars[]);
string_t* string_trim_left_to_new(string_t* first, char chars[]);


//trim a string, right side
//return value int, is the number of chars trimmed
int string_trim_right(string_t* first, char chars[]);
string_t* string_trim_right_to_new(string_t* first, char chars[]);


//substring of a string
string_t* string_substring(string_t* first, long from, size_t to);


//split of a string
//return an array of pointer to structs
string_t_array* string_split(string_t* first, char chars[]);


//compare a string
//check if two strings are euqals in time constant
//return 1 or 0
int string_compare(string_t* first, string_t* second);


//find inside a string
//todo, check for the proper return type
char* string_find_char(string_t* first, char c);
char* string_find_string_stt(string_t* first, string_t* second);
char* string_find_string_char(string_t* first, char chars[]);


//delete a string, free memory
void string_delete_stt(string_t* _string);
void string_delete_stt_array(string_t_array* _string);

#endif