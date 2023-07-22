/**
 * Copyright 2023 Sebastian Rapetti
 *
 * Part of the program Colonnade.
 * License - MIT
 */

#include <stdlib.h>
#include <stdbool.h>

#ifndef _COLUMNS_H
#define _COLUMNS_H 1

#define CHECK_POINTER(p)                                                              \
    if (!p)                                                                           \
    {                                                                                 \
        fprintf(stderr, "Null Pointer at line %d in file %s!\n", __LINE__, __FILE__); \
    }

#define OPEN_FILE(a, b, c)                          \
    if ((a = fopen(b, c)) == NULL)                  \
    {                                               \
        printf("[!] Cannot open the file %s\n", b); \
        return EXIT_FAILURE;                        \
    }

// labels
#define BYTES_NULL 0
#define BYTES_2 2
#define BYTES_4 3
#define BYTES_8 4
#define BYTES_16 16
#define BYTES_32 32
#define BYTES_64 64
#define BYTES_128 128
#define BYTES_256 256
#define BYTES_512 512
#define BYTES_1024 1024

/// @brief Count the number of bytes used by a single char in UTF-8.
///
/// @param byte the char to be checked.
///
/// @return the size of the char passed as byte.
///
size_t sizeof_char(size_t byte);

typedef struct _page_properties
{
    size_t column_size;
    size_t columns_per_page;
    size_t columns_spacing;
    size_t page_rows;
    size_t page_columns;
} page_properties, *p_page_properties;

// represents a row, as linked list of words
typedef struct _row
{
    size_t words;        // words in row
    size_t bytes;        // bytes used
    size_t chars;        // chars in row
    struct _word *first; // pointer to the first word in row

} row, *p_row;

// represents a word
typedef struct _word
{
    size_t bytes;         // bytes used
    size_t chars;         // chars in word
    bool is_space;        // true if the word is only spacing
    bool has_return;      // true if there is a \n or \r\n aftert
    bool start_paragraph; // true if there is more than one \n or \r\n before anc the word start a new paragraph
    char *word;           // pointer to word
    struct _word *next;   // pointer to the next struct when used as linked list

} word, *p_word;

// mantains data about the status of the array of rows
typedef struct _rows_array_status
{
    // as rows_array_populate_from_words
    size_t i; // word counter
    size_t j; // row counter
    size_t k; // justified row counter

    size_t *n_rows; // the number of allocated rows.

    p_row *input_rows; // array of rows

    p_word current_word;
    p_word next_word;

    p_row previous_row;
    p_row current_row;
    p_row next_row;

} rows_array_status, *p_rows_array_status;

/// @brief Allocate a new array of rows in heap.
///
/// @param n_rows the number of allocated rows.
///
/// @return the pointer to the new rows array.
///
p_row *rows_array_get(size_t n_rows);

/// @brief Extends an array of rows.
///
/// @param array      the array you want to extend.
/// @param old_n_rows the old number of allocated rows.
/// @param new_n_rows the new number of allocated rows.
///
/// @return the pointer to extended array.
///
p_row *rows_array_extend(p_row *array, size_t old_n_rows, size_t new_n_rows);

/// @brief
/// @param input_rows_array_status
/// @param word_size
/// @param column_size
/// @return
p_row *rows_array_populate_from_words_multiprocess(p_rows_array_status input_rows_array_status, size_t word_size, size_t column_size);

/// @brief Build an array of rows where every rows is justified an has a maximum size.
///
/// @param input_rows      the array of rows will be populated.
/// @param input_words     the array of words whre to get words to populate the array of rows.
/// @param n_rows          the number of allocated rows.
/// @param n_words         the number of allocated words.
/// @param word_size       the size in byte to allocate the word.
/// @param column_size the chars in a column.
///
/// @return the pointer to the populated array of rows.
///
p_row *rows_array_populate_from_words(p_row *input_rows, p_word *input_words, size_t *n_rows, size_t n_words, size_t word_size, size_t column_size);

/// @brief Returns the number of rows that have at least one word inside, allocated and used.
///
/// @param array  the array to check.
/// @param n_rows the number of elements allocated in array.
///
/// @return the number of non void words.
///
size_t rows_array_get_written(p_row *array, size_t n_rows);

/// @brief Free the memory allocated for the array.
///
/// @param array  the array to free.
/// @param n_rows the number of element in array.
///
void rows_array_free(p_row *array, size_t n_rows);

/// @brief Add a word to a row, this function allocate a new word and copy the passed one.
///
/// @param input_row  the row where to add the word.
/// @param input_word the word will be added to the row.
/// @param word_size  the size in byte to allocate the word.
///
void rows_array_add_word(p_row input_row, p_word input_word, size_t word_size);

/// @brief Align the text in a row both to left and to right margin
///
/// @param input_row       the row will be adjusted.
/// @param column_size the size where the row will be fit.
///
void row_justify(p_row input_row, size_t column_size);

/// @brief Transform the text formatted a single justified column into a text in multi columns and multi pages.
///
/// @param page             the matrix.
/// @param array            the array of rows.
/// @param rows_written     the number of rows in a single justified column.
/// @param row_offset       the first row will be added to the page.
/// @param page_offset      the page number expressed in rows per page.
/// @param page_p           the structure withe the properties of the page.
///
/// @return the number of rows written in page, where a row is a previous justified row of a column.
///
/// old declaration, befor grouping page properties
/// size_t page_add(char** page, p_row* array, size_t rows_written, size_t page_rows, size_t columns_spacing, size_t column_size, size_t columns_per_page, size_t row_offset, size_t page_offset);
size_t page_add(char **page, p_row *array, size_t rows_written, size_t row_offset, size_t page_offset, page_properties page_p);

/// @brief Allocate a new word in heap.
///
/// @param new_word  the word to be allocated in heap.
/// @param word_size the size in byte will be allocated.
///
/// @return the pointer to the new word array.
///
p_word word_get(word new_word, size_t word_size);

/// @brief Return a new array of words.
///
/// @param n_words   the number of allocated words.
/// @param word_size the size of a word in bytes.
///
/// @return the pointer to the new words array.
///
p_word *words_array_get(size_t n_words, size_t word_size);

/// @brief Extends an array of words.
///
/// @param array       the array you want to extend.
/// @param old_n_words the old number of allocated words.
/// @param new_n_words the new number of allocated words.
/// @param word_size   the size of a word in bytes.
///
/// @return the pointer to extended array.
///
p_word *words_array_extend(p_word *array, size_t old_n_words, size_t new_n_words, size_t word_size);

/// @brief Extends the space for a word inside an array of words.
///
/// @param array         the array that contains the word.
/// @param i_word        the index of the word.
/// @param new_word_size the new word size in bytes.
///
/// @return the pointer to extended array.
///
p_word *words_array_extend_word(p_word *array, size_t i_word, size_t new_word_size);

/// @brief Populate the array of words starting from a text file.
///
/// @param file_handle  the handle to file.
/// @param array        pointer to the array will be populated.
/// @param n_words      the pointer to the counter of allocated words.
/// @param word_max_len the pointer to the variable to get the number of chars for the longest word.
/// @param word_size    the size of a word in bytes.
///
/// @return the pointer to populated array, this because the array could be reallocated.
///
p_word *words_array_populate_from_file(FILE *file_handle, p_word *array, size_t *n_words, size_t *word_max_len, size_t word_size);

/// @brief Free the memory allocated for an array of words.
///
/// @param array   the array you wand to deallocate.
/// @param n_words the number of element in array.
///
void words_array_free(p_word *array, size_t n_words);

/// @brief Count chars in a word, utf-8 chars included.
///
/// @param word the pointer to the word.
///
/// @return the size of the word passed as argument.
///
size_t words_sizeof_word(char *word);

/// @brief Return a new array of pages, where a page is composed by multiple rows, every element of this array is a row.
///
/// @param rows    the number of rows for all pages.
/// @param row_len the len of the row, extra space will be allocated.
///
/// @return the pointer to the new pages array.
char **pages_get(size_t rows, size_t row_len);

/// @brief Write an array of rows into pages matrix.
///
/// @param pages          the pages matrix.
/// @param rows           the array of rows.
/// @param rows_in_array  the number of rows into the array of rows.
/// @param pages_required the number of pages required to write the array of rows.
/// @param page_p         the page properties.
///
void pages_write_rows(char **pages, p_row *rows, size_t rows_in_array, size_t pages_required, page_properties page_p);

/// @brief Free the memory allocated for an array of pages.
///
/// @param pages the array you want to deallocate.
/// @param wors  the number of element in array.
///
void pages_free(char **pages, size_t rows);

/// @brief Write the formatted output to file.
///
/// @param file_handle the handle to file where to write.
/// @param pages       the array of pages to write into the file.
/// @param rows        the number of the element in the array of pages.
///
void pages_write_to_file(FILE *file_handle, char **pages, size_t rows);

#endif /* columns.h */