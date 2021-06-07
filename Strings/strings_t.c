#include <stdlib.h>
#include "strings_t.h"


string_t* string_init_c(string_t* _string, char string[])
{
    if (_string) {
    
        int len = 0;
        //check for string lenght
        for (; string[len] != '\0'; len++);

        //assign struct
        *_string = (string_t) {
            .len = len,
            .len_null = len + 1,
            .string = malloc(len + 1)
        };

        //check for malloc
        if (!_string->string) {
            _string->len = 0;
            _string->len_null = 0;
            return _string;
        }

        //copy string
        for (int i = 0; i < len; _string->string[i] = string[i], i++); 

        //set nullbyte to the end of the string
        _string->string[len] = '\0';
    }
    else {
        *_string = (string_t) {0};
    }

    return _string;
}


static int string_concat_internal(string_t* first, char* second, size_t total_len)
{
    //realloc memory
    //make it safe
    char* p_tmp = realloc(first->string, total_len);
    
    //check if realloc fail, if yes
    //original pointer is preserved
    if (p_tmp) {
        //assign the new poinetr to string
        first->string = p_tmp;

        //copy second string
        //verify this cicle to avoid overflow with second variable
        for (int i = 0; (first->len + i) < (total_len - 1); first->string[first->len + i] = second[i], i++);
        
        //set new len
        first->len = total_len - 1;
        first->len_null = total_len;
        //set null byte at the end of the string
        first->string[total_len - 1] = '\0';

        return total_len;
    }

    return -1;
}


int string_concat_c(string_t* first, char* second)
{
    int len = 0;
    //check for string lenght
    for (; second[len] != '\0'; len++);
    
    //get total len with only last null bytes
    int total_len = first->len + len + 1;
    
    return string_concat_internal(first, second, total_len);
}


int string_concat_st(string_t* first, string_t* second)
{
    //get total len with only last null bytes
    int total_len = first->len + second->len_null;
    
    return string_concat_internal(first, second->string, total_len);
}


string_t* string_concat_to_new(string_t* first, string_t* second)
{
    //get total len with only last null bytes
    int total_len = first->len + second->len_null;

    //initialize the new string with the content of first string
    string_t* _string = string_init_c(malloc(sizeof(string_t)), first->string);

    //do concatenation, if fails return 0 string
    if (string_concat_internal(_string, second->string, total_len) == -1){
        *_string = (string_t) {0};
    }

    return _string;
}


string_t* string_copy(string_t *first)
{
    return string_init_c(malloc(sizeof(string_t)), first->string);
}


int string_trim_left(string_t* first, char chars[])
{
    int chars_len = 0;
    int trim = 0;

    //check for chars to trim length
    for (; chars[chars_len] != '\0'; chars_len++);

    for (int i = 0; i < first->len;) {
        //check for chars to trim
        for (int j = 0; j < chars_len; j++){
            if (first->string[i] == chars[j]) {
                trim++;
                break;
            }
        }
        //exit condition, if trim differs
        //from i then there where nothing to skipp
        //increment i before because skipp if always i + 1 
        //when char is found
        if (++i != trim) {
            break;
        }
    }

    //set new length
    first->len -= trim;
    first->len_null -= trim;
    
    //shift the string
    for (int i = 0; i < first->len; first->string[i] = first->string[trim + i], i++);

    //set new length and null byte
    first->string[first->len] = '\0';

    return trim;
}


int string_trim_right(string_t* first, char chars[])
{
    int chars_len = 0;
    int trim = 0;

    //check for chars to trim length
    for (; chars[chars_len] != '\0'; chars_len++);

    for (int i = first->len - 1; i >= 0;) {
        //check for chars to skipp
        for (int j = 0; j < chars_len; j++){
            if (first->string[i] == chars[j]) {
                trim++;
                break;
            }
        }
        //exit condition
        if ((first->len - 1) - --i != trim) {
            break;
        }
    }

    //set null byte at the end of the string
    first->len -= trim;
    first->len_null -= trim;
    first->string[first->len] = '\0';

    return trim;
}

/*string_t* string_trim_left(string_t* first, char chars[])
{
    int chars_len = 0;
    int skipp = 0;

    //check for chars to trim length
    for (; chars[chars_len] != '\0'; chars_len++);

    for (int i = 0; i < first->len;) {
        //check for chars to skipp
        for (int j = 0; j < chars_len; j++){
            if (first->string[i] == chars[j]) {
                skipp++;
                break;
            }
        }
        //exit condition, if skipp differs
        //from i then there where nothing to skipp
        //increment i before because skipp if always i + 1 
        //when char is found
        if (++i != skipp) {
            break;
        }
    }

    for (int i = 0; i <= (first->len - skipp); _string[i] = first->string[skipp + i], i++);

    return (string_t) {
        .len = first.len - skipp,
        .len_null = first.len - skipp + 1,
        .string = _string
    };
}*/

/*
string_t string_trim_right(char _string[], string_t first, char chars[])
{
    int chars_len = 0;
    int skipp = 0;

    //check for chars to trim length
    for (; chars[chars_len] != '\0'; chars_len++);

    for (int i = first.len - 1; i >= 0;) {
        //check for chars to skipp
        for (int j = 0; j < chars_len; j++){
            if (first.string[i] == chars[j]) {
                skipp++;
                break;
            }
        }
        //exit condition
        if ((first.len - 1) - --i != skipp) {
            break;
        }
    }

    int final_len = first.len - skipp;
    for (int i = 0; i < (final_len + 1); _string[i] = first.string[i], i++);

    //set null byte at the end of the string
    _string[final_len] = '\0';

    return (string_t) {
        .len = final_len,
        .len_null = final_len + 1,
        .string = _string
    };
}


string_t string_substring(char _string[], string_t first, int from, int to)
{
    int _from = from;
    int _to = to;

    //check for negative offsets
    //as start to the end of the string
    //if negative number i grather than string length
    //from start to zero
    if (from < 0) {
        _from = first.len + from;
        if (_from < 0) {
            _from = 0;
        }
    }

    //if from greater than string len, point to last char of the string
    if (from > first.len) {
        _from = first.len -1;
    }

    _to = _from + _to;
    if (_to > first.len) {
        _to = first.len;
    }

    //printf("[%d][%d]\n", _from, _to);
    int final_len = _to - _from;
    for (int i = 0; i < _to - _from; _string[i] = first.string[i + _from], i++);

    _string[final_len] = '\0';

    return (string_t) {
        .len = final_len,
        .len_null = final_len + 1,
        .string = _string
    };
}
*/

void string_delete(string_t* _string)
{
    if (_string) {
        _string->len = 0;
        _string->len_null = 0;
        free(_string->string);
        free(_string);
    }
}