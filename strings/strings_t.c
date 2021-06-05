#include <stdio.h>
#include "strings_t.h"

string_t string_init(char string[])
{
    int len = 0;
    //check for string lenght
    for (; string[len] != '\0'; len++);

    return (string_t) {
        .len = len,
        .len_null = len + 1,
        .string = string
    };
}


string_t string_concat(char _string[], string_t first, string_t second)
{
    //get total len without null bytes
    int total_len = first.len + second.len;
    
    //copy first string
    for (int i = 0; i < first.len; _string[i] = first.string[i], i++); 
    //copy second string
    for (int i = 0; i < total_len; _string[first.len + i] = second.string[i], i++);
    
    //set null byte at the end of the string
    _string[total_len] = '\0';

    return (string_t) {
        .len = total_len,
        .len_null = total_len + 1,
        .string = _string
    };
}


string_t string_copy(char _string[], string_t first)
{
    //copy string to buffer
    for (int i = 0; i <= first.len; _string[i] = first.string[i], i++);

    return (string_t) {
        .len = first.len,
        .len_null = first.len + 1,
        .string = _string
    };
}


string_t string_trim_left(char _string[], string_t first, char chars[])
{
    int chars_len = 0;
    int skipp = 0;

    //check for chars to trim length
    for (; chars[chars_len] != '\0'; chars_len++);

    for (int i = 0; i < first.len;) {
        //check for chars to skipp
        for (int j = 0; j < chars_len; j++){
            if (first.string[i] == chars[j]) {
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

    for (int i = 0; i <= (first.len - skipp); _string[i] = first.string[skipp + i], i++);

    return (string_t) {
        .len = first.len - skipp,
        .len_null = first.len - skipp + 1,
        .string = _string
    };
}


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


void string_zero(string_t first)
{
    for (int i = 0; i <= first.len; first.string[i++] = '\0');
}