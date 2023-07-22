/**
 * Copyright 2023 Sebastian Rapetti
 *
 * Part of the program Colonnade.
 * License - MIT
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "process_single.h"
#include "columns.h"

/// @brief Execute the program in single process manner.
///
/// @param input_file_name the name of the file to manipulate.
/// @param page_p          the properties of the page.
///
/// @return status code, 0 success other failure.
///
int single_process(char *input_file_name, page_properties page_p)
{
    CHECK_POINTER(input_file_name)

    ///////////////////////////////////////////
    /// Read file and create array of word ////
    ///////////////////////////////////////////

    // pointer to file handle
    FILE *input_file;
    FILE *output_file;

    // check if it's possible to open the input file
    OPEN_FILE(input_file, input_file_name, "r")

    // preallocated words for an array with 64 strings
    size_t words_allocated = BYTES_32;
    // preallocated bytes for a string of 128 bytes (127 + \0)
    size_t word_size = BYTES_128;
    // counter to find the size of the longest word in text, length in char
    size_t word_max_len = 0;

    printf("\n[+] Words:\n");

    // get a new array of words
    p_word *array_of_words = words_array_get(words_allocated, word_size);
    // populate array
    array_of_words = words_array_populate_from_file(input_file, array_of_words, &words_allocated, &word_max_len, word_size);

    printf("    - %ld words allocated\n", words_allocated);
    printf("    - longest word is %ld chars\n", word_max_len);

    // close handle
    fclose(input_file);

    // check for too small column size
    if (page_p.column_size < word_max_len)
    {
        printf("[!] longest word (%ld chars) is greather than the size of the column (%ld chars)\n", word_max_len, page_p.column_size);
        words_array_free(array_of_words, words_allocated);
        return EXIT_FAILURE;
    }

#ifdef _DEBUG
    for (size_t i = 0; i < words_allocated; i++)
    {
        if (array_of_words[i]->bytes)
        {
            printf("[d] {n: %ld, bytes: %ld, char: %ld, start_paragraph: %d, has_return: %d, word: \"%s\"}\n",
                   i,                                  // word number
                   array_of_words[i]->bytes,           // length in bytes
                   array_of_words[i]->chars,           // chars in word
                   array_of_words[i]->start_paragraph, // the word starts a paragraph
                   array_of_words[i]->has_return,      // does the word has a \n at the end
                   array_of_words[i]->word);           // the word
        }
    }
#endif

    ////////////////////////////////
    /// Array of justified rows ////
    ////////////////////////////////

    // starting rows
    // preallocated
    size_t rows_allocated = BYTES_8;
    // the number of row with words
    size_t rows_written = 0;
    // get the array of wors
    p_row *array_of_rows = rows_array_get(rows_allocated);

    // generate the array of words
    array_of_rows = rows_array_populate_from_words(array_of_rows, array_of_words, &rows_allocated, words_allocated, word_size, page_p.column_size);
    // check how many rows have been written
    rows_written = rows_array_get_written(array_of_rows, rows_allocated);

#ifdef _DEBUG
    for (size_t i = 0; i < rows_allocated; i++)
    {
        // current row shortcut
        p_row current_row = array_of_rows[i];

        // if the row has words inside
        if (current_row->words)
        {
            // get the head of the row
            p_word head = current_row->first;

            printf("[d] [row %ld] --> ", i);

            // loop the linked list
            while (head != NULL)
            {
                printf("[\"%s\"] --> ", head->word);
                head = head->next;
            }

            printf("[NULL]\n");
        }
    }
#endif

    printf("\n[+] Rows:\n");
    printf("    - %ld rows written\n", rows_written);
    printf("    - %ld rows allocated\n", rows_allocated);

    ///////////////////////////////
    /// Justified rows to page ////
    ///////////////////////////////

    // calculate required pages
    double tmp_pages_required = (double)rows_written / (double)(page_p.columns_per_page * page_p.page_rows);
    size_t pages_required = tmp_pages_required < 1 ? 1 : tmp_pages_required + 1;

    printf("\n[+] Page\n");
    printf("    - size [col]x[row] [%ld]x[%ld] chars\n", page_p.page_columns, page_p.page_rows);
    printf("    - chars per column %ld\n", page_p.column_size);
    printf("    - columns per page %ld\n", page_p.columns_per_page);
    printf("    - columns spacing %ld\n", page_p.columns_spacing);
    printf("    - pages required %ld\n", pages_required);
    printf("\n[+] Formatted text:\n\n");

    // allocate a page
    // extra rows provided per page to avoid overflow
    size_t page_total_rows = (page_p.page_rows + BYTES_8) * pages_required;
    // allocation
    char **pages = pages_get(page_total_rows, page_p.page_columns);

    // write the array of rows into the page
    pages_write_rows(pages, array_of_rows, rows_written, pages_required, page_p);

    ////////////////////////////
    /// Write pages to file ////
    ////////////////////////////

    // no overflow here
    char *output_file_name = calloc(strlen(input_file_name) + BYTES_16, sizeof(char));

    // create output file name
    strcat(output_file_name, "output.");
    strcat(output_file_name, input_file_name);

    // check if it's possiblee to open the output file
    OPEN_FILE(output_file, output_file_name, "w")

    // write to file
    pages_write_to_file(output_file, pages, page_total_rows);

    printf("\n[+] Output written to %s\n\n", output_file_name);

    // close output file handle
    fclose(output_file);

    /////////////////////
    /// Clean memory ////
    /////////////////////

    // release memory for filename
    free(output_file_name);

    // release memory for the pages
    pages_free(pages, page_total_rows);

    // release memory for the array of rows
    rows_array_free(array_of_rows, rows_allocated);

    // release memory for the array of words
    words_array_free(array_of_words, words_allocated);

    return EXIT_SUCCESS;
}