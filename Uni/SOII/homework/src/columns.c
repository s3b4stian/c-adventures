/**
 * Copyright 2023 Sebastian Rapetti
 *
 * Part of the program Colonnade.
 * License - MIT
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "columns.h"

/// @brief Count the number of bytes used by a single char in UTF-8.
///
/// @param byte the char to be checked.
///
/// @return the size of the char passed as byte.
///
size_t sizeof_char(size_t byte)
{
    // utf-8 char
    // f0 4 chars
    // e0 3 chars
    // c0|d0 2 chars, no check needed here
    if (byte > 0x7f)
    {
        // preserve only the hi nibble
        int hi_nibble = byte & 0xf0;

        // check for 4 bytes utf8 char
        if (hi_nibble == 0xf0)
        {
            return 4;
        }

        // check for 3 bytes utf8 char
        if (hi_nibble == 0xe0)
        {
            return 3;
        }

        // it's 2 bytes utf8 char
        // no need to check the nibble
        return 2;
    }

    return 1;
}

/// @brief Allocate a new array of rows in heap.
///
/// @param n_rows the number of allocated rows.
///
/// @return the pointer to the new rows array.
///
p_row *rows_array_get(size_t n_rows)
{
    // declaring the array
    p_row *p;
    // allocate the array of pointers
    // use the size of the pointer to row
    p = calloc(n_rows, sizeof(p_row));

    for (size_t i = 0; i < n_rows; i++)
    {
        // important sizeof(data type) in this case the row
        p[i] = calloc(1, sizeof(row));
    }

    return p;
}

/// @brief Extends an array of rows.
///
/// @param array      the array you want to extend.
/// @param old_n_rows the old number of allocated rows.
/// @param new_n_rows the new number of allocated rows.
///
/// @return the pointer to extended array.
///
p_row *rows_array_extend(p_row *array, size_t old_n_rows, size_t new_n_rows)
{
    CHECK_POINTER(array);

    array = realloc(array, new_n_rows * sizeof(p_row));

    for (size_t i = old_n_rows; i < new_n_rows; i++)
    {
        // important sizeof(data type)
        array[i] = calloc(1, sizeof(row));
    }

    return array;
}

/// @brief Build an array of rows where every rows is justified an has a maximum size, multiprocess version.
///        Difference between single process version and multi-process version is that this (multi-process version)
///        doesn't contain a loop inside and receive as argument a single word instead of an array of words.
///
/// @param ira_stat    the current status of the array of rows, input row array status.
/// @param word_size   the size in byte to allocate the word.
/// @param column_size the chars in a column.
///
/// @return the pointer to the populated array of rows.
///
p_row *rows_array_populate_from_words_multiprocess(p_rows_array_status ira_stat, size_t word_size, size_t column_size)
{
    CHECK_POINTER(ira_stat);
    // CHECK_POINTER(ira_stat->next_word);
    CHECK_POINTER(ira_stat->current_word);

    p_word next_word = ira_stat->next_word;
    p_row next_row;

    p_word current_word = ira_stat->current_word;
    p_row current_row;

    // p_word previous_word;
    p_row previous_row;

    // use designated initializers for the word
    // declared here for further use when a space
    // is needed
    word space = (word){
        .bytes = 1,
        .chars = 1,
        .is_space = true,
        .has_return = false,
        .start_paragraph = false,
        .word = " "};

    // printf("%ld >= %ld - %p\n", j, *n_rows, n_rows);

    // extends the array of rows
    // extends it when there are less than 4 elements free before the end
    // of the array, because below there is a jump of two positions for handle
    // a void row
    if (ira_stat->j >= (*(ira_stat->n_rows) - 4))
    {
        // printf("%ld >= %ld - %x\n", ira_stat->j, *(ira_stat->n_rows), ira_stat->n_rows);
        size_t old_rows = *(ira_stat->n_rows);
        *(ira_stat->n_rows) += 16;
        ira_stat->input_rows = rows_array_extend(ira_stat->input_rows, old_rows, *(ira_stat->n_rows));
        // printf("%ld >= %ld - %x\n", j, *n_rows, n_rows);
    }

    // skipp void but allocate words
    // happens because the resize of the words array allocates more space than needed
    if (!ira_stat->current_word->bytes)
    {
        return ira_stat->input_rows;
    }

    // shortcuts
    current_row = ira_stat->input_rows[ira_stat->j];

    // shortcut next rows
    next_row = NULL;
    if (ira_stat->j < *(ira_stat->n_rows))
    {
        next_row = ira_stat->input_rows[ira_stat->j + 1];
    }

    // shortcut previous row
    previous_row = NULL;
    if (ira_stat->j > 0)
    {
        previous_row = ira_stat->input_rows[ira_stat->j - 1];
    }

    // get previous row to justify it
    // only if j changed
    if (previous_row != NULL && ira_stat->j != ira_stat->k)
    {
        ira_stat->k = ira_stat->j;
        row_justify(previous_row, column_size);
    }

    // handle new paragraph
    if (next_word != NULL && next_word->start_paragraph)
    {
        // add word
        rows_array_add_word(current_row, current_word, word_size);
        // add space
        rows_array_add_word(next_row, &space, word_size);

        ira_stat->j += 2;

        return ira_stat->input_rows;
    }

    // add word to the row if the row has enough space
    if ((current_row->chars + current_word->chars) <= column_size)
    {
        // add word
        rows_array_add_word(current_row, current_word, word_size);

        if (current_word->has_return)
        {
            ira_stat->j++;
            // this skipp justify for a row that has one \n char at the end
            ira_stat->k = ira_stat->j;
        }

        // if there is a next word ad the this word+space fit then add a space
        if (next_word != NULL && (current_row->chars + next_word->chars + 1) <= column_size)
        {
            // add a space if there is possibility to add next word
            rows_array_add_word(current_row, &space, word_size);
        }
        else
        {
            ira_stat->j++;
        }
    }
    else
    {
        ira_stat->j++;
    }

    // printf("%ld: {bytes: %ld, char: %ld, first: %p}\n", i, current_row->bytes, current_row->chars, current_row->first);

    return ira_stat->input_rows;
}

/// @brief Build an array of rows where every rows is justified an has a maximum size.
///
/// @param input_rows      the array of rows will be populated.
/// @param input_words     the array of words whre to get words to populate the array of rows.
/// @param n_rows          the number of allocated rows.
/// @param n_words         the number of allocated words.
/// @param word_size       the size in byte to allocate the word.
/// @param column_size     the chars in a column.
///
/// @return the pointer to the populated array of rows.
///
p_row *rows_array_populate_from_words(p_row *input_rows, p_word *input_words, size_t *n_rows, size_t n_words, size_t word_size, size_t column_size)
{
    CHECK_POINTER(input_rows);
    CHECK_POINTER(input_words);
    CHECK_POINTER(n_rows);

    p_word next_word;
    p_row next_row;

    p_word current_word;
    p_row current_row;

    // p_word previous_word;
    p_row previous_row;

    // word counter
    size_t i = 0;
    // row counter
    size_t j = 0;
    // justified row counter
    // increment only when j change
    size_t k = 0;

    // use designated initializers for the word
    // declared here for further use when a space
    // is needed
    word space = (word){
        .bytes = 1,
        .chars = 1,
        .is_space = true,
        .has_return = false,
        .start_paragraph = false,
        .word = " "};

    // printf("%ld >= %ld - %p\n", j, *n_rows, n_rows);

    for (i = 0; i < n_words; i++)
    {
        // extends the array of rows
        // extends it when there are less than 4 elements free before the end
        // of the array, because below there is a jump of two positions for handle
        // a void row
        if (j >= (*n_rows - 4))
        {
            // printf("%ld >= %ld - %x\n", j, *n_rows, n_rows);
            size_t old_rows = *n_rows;
            *n_rows += 16;
            input_rows = rows_array_extend(input_rows, old_rows, *n_rows);
            // printf("%ld >= %ld - %x\n", j, *n_rows, n_rows);
        }

        // skipp void but allocate words
        // happens because the resize of the words array allocates more space than needed
        if (!input_words[i]->bytes)
        {
            continue;
        }

        // shortcuts
        current_word = input_words[i];
        current_row = input_rows[j];

        // printf("%s\n", current_word->word);

        // shortcut next word
        next_word = NULL;
        if (i + 1 < n_words)
        {
            next_word = input_words[i + 1];
            // printf(" next word: -- %ld -- \n", next_word->bytes);
        }

        // shortcut next rows
        next_row = NULL;
        if (j < *n_rows)
        {
            next_row = input_rows[j + 1];
        }

        // shortcut previous row
        previous_row = NULL;
        if (j > 0)
        {
            previous_row = input_rows[j - 1];
        }

        // get previous row to justify it
        // only if j changed
        if (previous_row != NULL && j != k)
        {
            k = j;
            row_justify(previous_row, column_size);
        }

        // handle new paragraph
        if (next_word != NULL && next_word->start_paragraph)
        {
            // add word
            rows_array_add_word(current_row, current_word, word_size);
            // add space
            rows_array_add_word(next_row, &space, word_size);

            j += 2;
            continue;
        }

        // add word to the row if the row has enough space
        if ((current_row->chars + current_word->chars) <= column_size)
        {
            // add word
            rows_array_add_word(current_row, current_word, word_size);

            if (current_word->has_return)
            {
                j++;
                // this skipp justify for a row that has one \n char at the end
                k = j;
            }

            // if there is a next word ad the this word+space fit then add a space
            if (next_word != NULL && (current_row->chars + next_word->chars + 1) <= column_size)
            {
                // add a space if there is possibility to add next word
                rows_array_add_word(current_row, &space, word_size);
            }
            else
            {
                j++;
            }
        }
        else
        {
            j++;
        }

        // printf("%ld: {bytes: %ld, char: %ld, first: %p}\n", i, current_row->bytes, current_row->chars, current_row->first);
    }

    return input_rows;
}

/// @brief Returns the number of rows that have at least one word inside, allocated and used.
///
/// @param array  the array to check.
/// @param n_rows the number of elements allocated in array.
///
/// @return the number of non void words.
///
size_t rows_array_get_written(p_row *array, size_t n_rows)
{
    CHECK_POINTER(array);

    size_t i;
    // start from the end of the array
    for (i = n_rows - 1; i > 0; i--)
    {
        if (array[i]->words)
        {
            break;
        }
    }

    return ++i;
}

/// @brief Free the memory allocated for the array.
///
/// @param array  the array to free.
/// @param n_rows the number of element in array.
///
void rows_array_free(p_row *array, size_t n_rows)
{
    CHECK_POINTER(array);

    // free the row and the structure
    for (size_t i = 0; i < n_rows; i++)
    {

        // first word in row
        p_word head = array[i]->first;
        p_word tmp_head;

        if (head != NULL)
        {
            // free component of linked list
            while (head->next != NULL)
            {
                // set the head to next node
                tmp_head = head->next;

                // unlink
                head->next = NULL;

                // free memoty
                free(head->word);
                free(head);

                // new head
                head = tmp_head;
            }

            // the last head
            free(head->word);
            free(head);
        }

        // free the row
        free(array[i]);
    }

    // free the array of pointers
    free(array);
}

/// @brief Add a word to a row, this function allocate a new word and copy the passed one.
///
/// @param input_row  the row where to add the word.
/// @param input_word the word will be added to the row.
/// @param word_size  the size in byte to allocate the word.
///
void rows_array_add_word(p_row input_row, p_word input_word, size_t word_size)
{
    CHECK_POINTER(input_row);
    CHECK_POINTER(input_word);

    // allocate memory for new word
    p_word tmp_word = word_get(*input_word, word_size);

    // increment rows stats
    input_row->bytes += tmp_word->bytes;
    input_row->chars += tmp_word->chars;
    input_row->words++;

    // if the word is the first of the row
    if (input_row->first == NULL)
    {
        input_row->first = tmp_word;
        return;
    }

    // else traverse the linked list
    // first word in row
    p_word head = input_row->first;
    while (head->next != NULL)
    {
        head = head->next;
    }

    // add the word at the end of the list
    head->next = tmp_word;
}

/// @brief Align the text in a row both to left and to right margin
///
/// @param input_row       the row will be adjusted.
/// @param column_size the size where the row will be fit.
///
void row_justify(p_row input_row, size_t column_size)
{
    CHECK_POINTER(input_row);

    size_t required_spaces = column_size - input_row->chars;

    // to avoid infinite loops
    size_t has_spaces = false;
    // get the first word in row
    p_word head = input_row->first;

    if (head == NULL)
    {
        return;
    }

    while (required_spaces)
    {
        if (head->is_space)
        {
            has_spaces = true;

            // should be memory for 127 spaces
            // more than the number of chars in row for a page
            strcat(head->word, " ");

            // increment word stats
            head->chars++;
            head->bytes++;

            // increment row stats
            input_row->chars++;
            input_row->bytes++;

            required_spaces--;
        }

        // end of the list, restart
        if (head->next == NULL)
        {
            // avoid infinite loop if a row don' contain spaces
            if (!has_spaces)
            {
                break;
            }
            // restart the head
            head = input_row->first;
            continue;
        }

        // next element in the list
        head = head->next;
    }
}

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
/// size_t page_add(char** page, p_row* array, size_t rows_written, size_t page_rows, size_t columns_spacing, size_t column_size, size_t columns_per_page, size_t row_offset, size_t page_offset)
size_t page_add(char **page, p_row *array, size_t rows_written, size_t row_offset, size_t page_offset, page_properties page_p)
{
    CHECK_POINTER(page);
    CHECK_POINTER(array);

    // page matrix coordinates
    size_t page_x = 0;
    size_t page_y = 0;

    // column in current page
    size_t column = 0;

    // extra spaces to write when there is a multibyte char
    size_t *m_spaces = calloc(page_p.page_rows, sizeof(size_t));

    // it should explain itself
    // indicate the max number of rows from the array of rows per page
    size_t max_rows_page = page_p.page_rows * page_p.columns_per_page;

    // number of current row
    size_t i;

    // printf("--r:%ld\n",row_offset);

    // start to loop the rows
    for (i = row_offset; i < rows_written; i++)
    {
        // printf("i:%ld\n",i);
        p_row current_row = array[i];

        // if the row has words
        if (current_row->words)
        {
            // calculate column
            page_x = (column * page_p.column_size);
            page_x += page_p.columns_spacing * column + m_spaces[page_y];

            // fill the new row with spaces
            // this because unesed rows remains filled with null bytes
            // and is easier skip them
            // moreover filling with spaces before write words avoid to have to
            // write separators between columns
            if (page_x == 0)
            {
                for (size_t j = 0; j < page_p.page_columns; j++)
                {
                    page[page_offset + page_y][j] = 0x20;
                }
            }

            p_word head = current_row->first;

            // printf("-- i: %ld ",i);

            // write words to page
            while (head != NULL)
            {
                // printf(" [%ld][%ld] %s", page_offset + page_y, page_x, head->word);
                // printf("%s", head->word);
                memcpy(&(page[page_offset + page_y][page_x]), head->word, head->bytes);
                // consider more spaces for chars that use multibyte
                m_spaces[page_y] += head->bytes - head->chars;

                page_x += head->bytes;
                head = head->next;
            }

            // printf("\n");

            // increment row
            page_y++;
        }

        // break when page filled
        if ((i - row_offset) == max_rows_page)
        {
            page_y++;
            break;
        }

        // if end of the page reached reset row and increment column
        if (page_p.page_rows == page_y)
        {
            column++;
            page_y = 0;
        }
    }

    free(m_spaces);

    return i;
}

/// @brief Allocate a new word in heap.
///
/// @param new_word  the word to be allocated in heap.
/// @param word_size the size in byte will be allocated.
///
/// @return the pointer to the new word array.
///
p_word word_get(word new_word, size_t word_size)
{
    // alloracte memory
    p_word tmp_word = calloc(1, sizeof(word));

    // make a copy of the word to put into row
    memcpy(tmp_word, &new_word, sizeof(word));

    // overwrite things
    tmp_word->next = NULL;
    tmp_word->word = calloc(word_size, sizeof(char));

    // make a copy of the string of the word
    memcpy(tmp_word->word, new_word.word, word_size);

    return tmp_word;
}

/// @brief Return a new array of words.
///
/// @param n_words   the number of allocated words.
/// @param word_size the size of a word in bytes.
///
/// @return the pointer to the new words array.
///
p_word *words_array_get(size_t n_words, size_t word_size)
{
    // delaring the array
    // remember that string is equal to char*, in like write char**
    p_word *p;
    // important sizeof(pointer)
    // allocate the array of pointers
    // use the size of the word
    p = calloc(n_words, sizeof(p_word));
    // declaring columns
    for (size_t i = 0; i < n_words; i++)
    {
        // important sizeof(data type)
        p[i] = calloc(1, sizeof(word));
        p[i]->word = calloc(word_size, sizeof(char));
        p[i]->next = NULL;
    }

    return p;
}

/// @brief Extends an array of words.
///
/// @param array       the array you want to extend.
/// @param old_n_words the old number of allocated words.
/// @param new_n_words the new number of allocated words.
/// @param word_size   the size of a word in bytes.
///
/// @return the pointer to extended array.
///
p_word *words_array_extend(p_word *array, size_t old_n_words, size_t new_n_words, size_t word_size)
{
    CHECK_POINTER(array);

    array = realloc(array, new_n_words * sizeof(p_word));

    for (size_t i = old_n_words; i < new_n_words; i++)
    {
        // important sizeof(data type)
        array[i] = calloc(1, sizeof(word));
        array[i]->word = calloc(word_size, sizeof(char));
        array[i]->next = NULL;
    }

    return array;
}

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
p_word *words_array_populate_from_file(FILE *file_handle, p_word *array, size_t *n_words, size_t *word_max_len, size_t word_size)
{
    CHECK_POINTER(file_handle);
    CHECK_POINTER(array);
    CHECK_POINTER(n_words);
    CHECK_POINTER(word_max_len);

    // current char read from file
    // int because EOF is -1
    int byte = 0;
    size_t prev_byte = 0;

    // the number of bytes inside file
    size_t file_size_bytes = 0;

    // i for the row and j for the string
    size_t i = 0;
    size_t j = 0;

    // get all bytes
    while ((byte = fgetc(file_handle)) != EOF)
    {
        file_size_bytes += 1;

        // if there is no more space on array
        // increment the array
        if (i == *n_words)
        {
            size_t old_words = *n_words;
            *n_words += 32;
            array = words_array_extend(array, old_words, *n_words, word_size);
        }

        // skipp \r char
        // preserve only \n chars
        // hate windows and this also transform \r\n in \n
        // avoid this function to parse http messages
        // don't use it on windows systems
        if (byte == 0x0d)
        {
            continue;
        }

        // skip multple spaces
        if (byte == 0x20 && prev_byte == 0x20)
        {
            continue;
        }

        // truncate a word
        // new element of trhe array
        if (
            (byte == 0x20 && prev_byte != 0x20) || // spaces, avoid multiple
            (byte == 0x11) ||                      // horizontal tab
            (byte == 0x13) ||                      // vertical tab
            (byte == 0x0a))
        {

            // multiple new line set the end of the paragraph
            if (byte == 0x0a && prev_byte == 0x0a)
            {
                // store only previous byte
                prev_byte = byte;

                array[i]->start_paragraph = 1;
                continue;
            }

            // single new line set the return
            if (byte == 0x0a && prev_byte != 0x0a)
            {
                array[i]->has_return = 1;
            }

            array[i]->chars = words_sizeof_word(array[i]->word);

            // get the max len for words in file
            if (*word_max_len < array[i]->chars)
            {
                *word_max_len = array[i]->chars;
            }

            // store previous byte
            prev_byte = byte;
            // new word
            i++;
            // reset word size
            j = 0;

            continue;
        }

        array[i]->bytes++;
        array[i]->word[j] = byte;

        // store previous byte
        prev_byte = byte;
        // new byte
        j++;
    }

    printf("    - %lu bytes read\n", file_size_bytes);
    printf("    - %lu words written\n", i);

    return array;
}

/// @brief Free the memory allocated for an array of words.
///
/// @param array   the array you want to deallocate.
/// @param n_words the number of element in array.
///
void words_array_free(p_word *array, size_t n_words)
{
    CHECK_POINTER(array);

    // free the word and the structure
    for (size_t i = 0; i < n_words; i++)
    {
        free(array[i]->word);
        free(array[i]);
    }

    // free the array of pointers
    free(array);
}

/// @brief Count chars in a word, utf-8 chars included.
///
/// @param word the pointer to the word.
///
/// @return the size of the word passed as argument.
///
size_t words_sizeof_word(char *word)
{
    CHECK_POINTER(word);

    size_t word_length_char = 0;
    size_t i = 0;
    size_t byte = word[i];

    while (byte)
    {
        // increment the length
        word_length_char++;
        // set to jump n positions
        i += sizeof_char(byte);
        byte = word[i];
    }

    return word_length_char;
}

/// @brief Return a new array of pages, where a page is composed by multiple rows, every element of this array is a row.
///
/// @param rows    the number of rows for all pages.
/// @param row_len the len of the row, extra space will be allocated.
///
/// @return the pointer to the new pages array.
char **pages_get(size_t rows, size_t row_len)
{
    // the page
    char **pages = calloc(rows, sizeof(char *));
    // row space, extra space added
    size_t page_columns_extra_space = row_len + BYTES_64;
    // allocate memory for every row
    for (size_t i = 0; i < rows; i++)
    {
        pages[i] = calloc(page_columns_extra_space, sizeof(char));
    }

    return pages;
}

/// @brief Write an array of rows into pages matrix.
///
/// @param pages          the pages matrix.
/// @param rows           the array of rows.
/// @param rows_in_array  the number of rows into the array of rows.
/// @param pages_required the number of pages required to write the array of rows.
/// @param page_p         the page properties.
///
void pages_write_rows(char **pages, p_row *rows, size_t rows_in_array, size_t pages_required, page_properties page_p)
{
    CHECK_POINTER(pages)
    CHECK_POINTER(rows)

    size_t row_offset = 0;
    size_t page_offset = 0;
    char *page_separator = "\n%%%\n";

    // loop for every page
    for (size_t i = 0; i < pages_required; i++)
    {
        // page offset for the y axis
        page_offset = (page_p.page_rows * i) + i;

        // add the page separator on top of every page if there is more than one page
        if (i > 0)
        {
            // copy the page separator
            memcpy(&(pages[page_offset][0]), page_separator, 6);
            page_offset++;
        }

        // add the page
        // every row in array_of_wors copied to page into the correct column
        // following this order
        //  --      --      --      -- --       -- --      -- --
        //      ->  --  ->  --  ->  --     -->  -- --  ->  -- --
        //                  --      --          --         -- --
        // when the page is full return the row written to the page
        // row_offset variable is passed in next loop as argument
        row_offset = page_add(pages, rows, rows_in_array, row_offset, page_offset, page_p);
    }
}

/// @brief Free the memory allocated for an array of pages.
///
/// @param pages the array you want to deallocate.
/// @param wors  the number of element in array.
///
void pages_free(char **pages, size_t rows)
{
    CHECK_POINTER(pages);

    // free every row in pages
    for (size_t i = 0; i < rows; i++)
    {
        free(pages[i]);
    }

    free(pages);
}

/// @brief Write the formatted output to file.
///
/// @param file_handle the handle to file where to write.
/// @param pages       the array of pages to write into the file.
/// @param rows        the number of the element in the array of pages.
///
void pages_write_to_file(FILE *file_handle, char **pages, size_t rows)
{
    CHECK_POINTER(file_handle);
    CHECK_POINTER(pages);

    for (size_t i = 0; i < rows; i++)
    {
        if (pages[i][0] != 0x00)
        {
            printf("%s\n", pages[i]);
            fprintf(file_handle, "%s\n", pages[i]);
        }
    }
}