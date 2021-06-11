#include <stdlib.h>
#include "strings_t.h"


string_t* string_init_from_void(string_t* _string, size_t len)
{
    if (_string) {
    
        //assign struct
        *_string = (string_t) {
            .len = len,
            .len_null = len + 1,
            .string = calloc(len + 1, 1)
        };

        //check for calloc
        if (!_string->string) {
            _string->len = 0;
            _string->len_null = 0;
            return _string;
        }
    }
    else {
        *_string = (string_t) {0};
    }

    return _string;
}


string_t* string_init_from_char_len(string_t* _string, char string[], size_t len)
{
    if (_string) {
    
        //assign struct
        *_string = (string_t) {
            .len = len,
            .len_null = len + 1,
            .string = calloc(len + 1, 1)
        };

        //check for calloc
        if (!_string->string) {
            _string->len = 0;
            _string->len_null = 0;
            return _string;
        }

        //copy string
        for (size_t i = 0; i < len; _string->string[i] = string[i], i++); 

        //set nullbyte to the end of the string
        _string->string[len] = '\0';
    }
    else {
        *_string = (string_t) {0};
    }

    return _string;
}


string_t* string_init_from_char(string_t* _string, char string[])
{
    size_t len = 0;
    //check for string lenght
    for (; string[len] != '\0'; len++);

    return string_init_from_char_len(_string, string, len);
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
        for (size_t i = 0; (first->len + i) < (total_len - 1); first->string[first->len + i] = second[i], i++);
        
        //set new len
        //in this case total_len include the final null byte
        first->len = total_len - 1;
        first->len_null = total_len;
        //set null byte at the end of the string
        first->string[total_len - 1] = '\0';

        return total_len - 1;
    }

    return -1;
}


int string_concat_char(string_t* first, char* second)
{
    size_t len = 0;
    //check for string lenght
    for (; second[len] != '\0'; len++);
    
    //get total len with only last null bytes
    size_t total_len = first->len + len + 1;
    
    return string_concat_internal(first, second, total_len);
}


int string_concat_stt(string_t* first, string_t* second)
{
    //get total len with only last null bytes
    size_t total_len = first->len + second->len_null;
    
    return string_concat_internal(first, second->string, total_len);
}


string_t* string_concat_to_new(string_t* first, string_t* second)
{
    //get total len with only last null bytes
    size_t total_len = first->len + second->len_null;

    //initialize the new string with the content of first string
    string_t* _string = string_init_from_char_len(calloc(1, sizeof(string_t)), first->string, first->len);

    //do concatenation, if fails return 0 string
    if (string_concat_internal(_string, second->string, total_len) == -1){
        *_string = (string_t) {0};
    }

    return _string;
}


string_t* string_copy(string_t *first)
{
    return string_init_from_char_len(calloc(1, sizeof(string_t)), first->string, first->len);
}


int string_trim_left(string_t* first, char chars[])
{
    size_t chars_len = 0;
    size_t trim = 0;

    //check for chars to trim length
    for (; chars[chars_len] != '\0'; chars_len++);

    for (size_t i = 0; i < first->len;) {
        //check for chars to trim
        for (size_t j = 0; j < chars_len; j++){
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
    for (size_t i = 0; i < first->len; first->string[i] = first->string[trim + i], i++);

    //set new length and null byte
    first->string[first->len] = '\0';

    return trim;
}


string_t* string_trim_left_to_new(string_t* first, char chars[])
{
    string_t* _string = string_init_from_char_len(calloc(1, sizeof(string_t)), first->string, first->len);

    if (_string) {
        string_trim_left(_string, chars);
    }

    return _string;
}


int string_trim_right(string_t* first, char chars[])
{
    //size_t chars_len = 0;
    size_t trim = 0;

    //check for chars to trim length
    //for (; chars[chars_len] != '\0'; chars_len++);

    for (size_t i = first->len - 1; i >= 0;) {
        //check for chars to skipp
        for (size_t j = 0; chars[j] != '\0'; j++) {
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


string_t* string_trim_right_to_new(string_t* first, char chars[])
{
    string_t* _string = string_init_from_char_len(calloc(1, sizeof(string_t)), first->string, first->len);

    if (_string) {
        string_trim_right(_string, chars);
    }

    return _string;
}


string_t* string_substring(string_t* first, long from, size_t to)
{
    long _from = from;
    size_t _to = to;

    //check for negative offsets
    //as start to the end of the string
    if (_from < 0) {
        //remove the minus sign
        //compare a negavive long and a size_t has weird result
        _from = -_from;
    
        if (_from < first->len) {
            _from = first->len - _from;
        }

        if (_from >= first->len) {
            _from = 0;
        }
    }
    else if (_from >= first->len) {
        _from = first->len - 1;
    }
    //check for how many chars to extract
    _to = _from + _to;
    if (_to > first->len - 1) {
        _to = first->len;
    }

    //calculate final length without null byte
    int final_len = _to - _from;

    //init a new void string length
    //null byte space added automatically by string_init_void
    string_t* _string = string_init_from_void(calloc(1, sizeof(string_t)), final_len);
    
    if (_string) {
        //copy the content of the string
        for (size_t i = 0; i < _to - _from; _string->string[i] = first->string[i + _from], i++);

        _string->string[final_len] = '\0';
    }

    return _string;
    
}


string_t_array* string_split(string_t* first, char chars[])
{
    //copy of the string
    string_t* _string = string_init_from_char_len(calloc(1, sizeof(string_t)), first->string, first->len);

    //number of token
    int token = 0;
    for (size_t i = 0; i < _string->len; i++) {
        //check for chars to skipp
        //replace them with null bytes
        for (size_t j = 0; chars[j] != '\0'; j++) {
            
            if (first->string[i] == chars[j]) {
                token++;
                
                _string->string[i] = '\0';
                break;
            }
        }
    }

    string_t_array* 
    _string_array = calloc(1, sizeof(string_t_array));
    _string_array->len = 0;
    _string_array->strings = calloc(++token, sizeof(string_t*));
    
    for (size_t i = 0; i < _string->len; i++) { 
        //null byte
        if (!_string->string[i]) {
            continue;
        }
        
        //i equal to zero and null byte
        if (!i && !_string->string[i]) {
            continue;
        }

        //i greater than zero, char of i an i-1 not null byte
        //a char inside other chars
        if (i && _string->string[i] && _string->string[i - 1]) {
            continue;
        }        

        _string_array->strings[_string_array->len++] = string_init_from_char(calloc(1, sizeof(string_t)), _string->string + i);
    }

    //free the copy of the string
    string_delete_stt(_string);

    return _string_array;
}


int string_compare(string_t* first, string_t* second)
{
    size_t len = 0;
    size_t res = 0;

    //check for the longer string
    if (first->len > second->len) {
        len = second->len;
        res = 1;
    }

    //check for the longer string
    if (first->len < second->len) {
        len = first->len;
        res = 1;
    }

    //check for equals strings
    if (first->len == second->len) {
        len = first->len;
        res = 0;
    }

    //compare strings for the size of the shorter string
    //if the length of the string is different
    //res will be already not zero
    for (size_t i = 0; i < len; i++) {
        //bitwise xor ^ of 2 equals == 0
        //bitwise or |= return 1 if at least one is true
        res |= first->string[i] ^ second->string[i];
    }

    return res == 0;
}


void string_delete_stt(string_t* _string)
{
    if (_string) {
        //delete the string from heap
        for (size_t i = 0; i < _string->len_null; _string->string[i] = '\0', i++);

        _string->len = 0;
        _string->len_null = 0;
        free(_string->string);
        free(_string);

        _string = ((void*)0);
    }
}


void string_delete_stt_array(string_t_array* _string)
{
    if (_string) {
        //free every string on array
        for (size_t i = 0; i < _string->len; string_delete_stt(_string->strings[i]), i++);
        //free the pointer of pointer
        free(_string->strings);
        //free the array struct
        free(_string);

        _string = ((void*)0);
    }
}