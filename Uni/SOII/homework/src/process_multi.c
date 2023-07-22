/**
 * Copyright 2023 Sebastian Rapetti
 *
 * Part of the program Colonnade.
 * License - MIT
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>

#include "columns.h"
#include "process_multi.h"

// semaphores
// named semaphores
// https://man7.org/linux/man-pages/man7/sem_overview.7.html
// between 1st and 2nd child processes
const char *name_sem_file_reader = "/file_reader";
const char *name_sem_columnist = "/columnist";
// between 2nd and 3rd child processes
const char *name_sem_columnist_pw = "/columnist_pw";
const char *name_sem_page_writer = "/page_writer";
// between 3rd and 4th child processes
const char *name_sem_page_writer_fw = "/page_writer_fw";
const char *name_sem_file_writer = "/file_writer";

/// @brief A wrapper to mmap function.
///
/// @param size the number of bytes required.
///
/// @return the pointer to shared memory-
///
void *shared_memory_get(size_t size)
{
    // https://man7.org/linux/man-pages/man2/mmap.2.html
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
}

/// @brief Child process to read file and create array of word.
//
/// @param input_file_name the name file to read words.
/// @param mem_map         the structure with shared memory pointer.
/// @param page_p          the structure with page properties.
///
/// @return the exit status.
///
int child_file_reader(char *input_file_name, shared_memory_map mem_map, semaphores_map sm, page_properties page_p)
{
    CHECK_POINTER(input_file_name)

    // put the columnist process in wait
    SEM_WAIT(sm.columnist)

    // pointer to file handle
    FILE *input_file;

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
        // close all semaphores
        SEM_CLOSE_ALL(sm)
        return EXIT_FAILURE;
    }

    // write word allocated to shared memory
    memcpy(mem_map.words_allocated, &words_allocated, sizeof(size_t));
    // also pass the size of the word
    memcpy(mem_map.word_size, &word_size, sizeof(size_t));

    SEM_POST(sm.file_reader)

    // loop all words
    // put the on shared memory one to one
    for (size_t i = 0; i < words_allocated; i++)
    {
        SEM_WAIT(sm.columnist)

        memset(mem_map.struct_word, 0, sizeof(word));
        memset(mem_map.word, 0, word_size);

        if (array_of_words[i]->bytes)
        {
            // printf("[+] File Reader\n");
            // printf("    - [FR sem_wait] sem_columnist\n");

            memcpy(mem_map.struct_word, array_of_words[i], sizeof(word));
            memcpy(mem_map.word, array_of_words[i]->word, array_of_words[i]->bytes);
            mem_map.struct_word->word = mem_map.word;

            // printf("    - [FR sem_post] sem_file_reader\n");
        }

        SEM_POST(sm.file_reader)
    }

    // release memory for the array of words
    words_array_free(array_of_words, words_allocated);

    // close all semaphores
    SEM_CLOSE_ALL(sm)

    return EXIT_SUCCESS;
}

/// @brief Child process to create array of justified rows.
///
/// @param mem_map         the structure with shared memory pointer.
/// @param page_p          the structure with page properties.
///
/// @return the exit status.
///
int child_columnist(shared_memory_map mem_map, semaphores_map sm, page_properties page_p)
{
    // wait
    // read shared memory
    SEM_WAIT(sm.file_reader)
    // copy shared memory
    size_t words_allocated = *(mem_map.words_allocated);
    size_t word_size = *(mem_map.word_size);

    SEM_POST(sm.columnist)

    // starting rows
    // preallocated
    size_t rows_allocated = BYTES_8;
    // the number of row with words
    size_t rows_written = 0;

    // row status structure
    // matains the status for the array of rows
    // mainly created to avoid a function with 2*10^78 paramethers
    rows_array_status ras;
    // counters
    ras.i = 0;
    ras.j = 0;
    ras.k = 0;

    // get the array of wors
    ras.input_rows = rows_array_get(rows_allocated);
    ras.n_rows = &rows_allocated;

    CHECK_POINTER(ras.input_rows);

    // nullify all things
    ras.current_word = NULL;
    ras.next_word = NULL;

    ras.previous_row = NULL;
    ras.current_row = NULL;
    ras.next_row = NULL;

    p_word temp_word = NULL;

    bool last_word = true;

    // loop allocated words from
    for (size_t i = 0; i < words_allocated; i++)
    {
        SEM_WAIT(sm.file_reader)

        // printf("[+] Columnist\n");
        // printf("    - [C sem_wait] sem_file_reader\n");
        // printf("    - Critical\n");

        // printf("    *** %s * %ld * %ld * %ld * %ld * %ld ***\n", shared_st_word->word, shared_st_word->bytes, i, i % 2, words_allocated, word_size);

        // to use the function rows_array_populate_from_words written
        // for singleprocess version know which is the next word inside
        // the array is mandatory to emulate this the function who
        // populate the array of rows is called one time every two words
        // passed to the current process.
        // the solution permit to reuse almost all code but brings other
        if (mem_map.struct_word->bytes)
        {
            // get the current word from shared memory
            p_word received_word = word_get(*mem_map.struct_word, word_size);

            // first word passed is stored temporarily
            if (i == 0)
            {
                temp_word = received_word;
            }
            // when the second word arrives, the temp word become the current
            // and the second the next
            else if (i == 1)
            {
                ras.current_word = temp_word;
                ras.next_word = received_word;
                ras.input_rows = rows_array_populate_from_words_multiprocess(&ras, word_size, page_p.column_size);
            }
            // from the third word, the old next become the current
            // and current word is the new next, the loop works with
            // a delay of one word
            else
            {
                free(ras.current_word->word);
                free(ras.current_word);

                ras.current_word = ras.next_word;
                ras.next_word = received_word;
                ras.input_rows = rows_array_populate_from_words_multiprocess(&ras, word_size, page_p.column_size);
            }
        }
        // no more words
        // the old next become the current and the new next is NULL
        else if (last_word)
        {
            free(ras.current_word->word);
            free(ras.current_word);

            ras.current_word = ras.next_word;
            ras.next_word = NULL;
            ras.input_rows = rows_array_populate_from_words_multiprocess(&ras, word_size, page_p.column_size);

            free(ras.current_word->word);
            free(ras.current_word);

            last_word = false;
        }

        // printf("    - [C sem_post] sem_columnist\n");

        SEM_POST(sm.columnist)
    }

    rows_written = rows_array_get_written(ras.input_rows, rows_allocated);

    printf("\n[+] Rows:\n");
    printf("    - %ld rows written\n", rows_written);
    printf("    - %ld rows allocated\n", rows_allocated);

    // send the number of rows written to the page writer
    SEM_WAIT(sm.page_writer)
    // copy to shared memory the number of rows written
    memcpy(mem_map.rows_written, &rows_written, sizeof(size_t));
    SEM_POST(sm.columnist_pw)

    // send rows to page writer
    for (size_t i = 0; i < rows_written; i++)
    {
        p_row current_row = ras.input_rows[i];

        // inform the page writer about the number of word in current row
        SEM_WAIT(sm.page_writer)
        memcpy(mem_map.words_allocated, &current_row->words, sizeof(size_t));
        SEM_POST(sm.columnist_pw)

        // printf("%ld: ", current_row->words);

        if (current_row->words)
        {
            p_word head = current_row->first;

            // printf("Sending row of %ld words: ", current_row->words);
            while (head != NULL)
            {
                SEM_WAIT(sm.page_writer)

                // printf("%s", head->word);

                memset(mem_map.struct_word, 0, sizeof(word));
                memset(mem_map.word, 0, word_size);

                //  printf("[+] File Reader\n");
                //  printf("    - [FR sem_wait] sem_columnist\n");

                memcpy(mem_map.struct_word, head, sizeof(word));
                memcpy(mem_map.word, head->word, head->bytes);
                mem_map.struct_word->word = mem_map.word;

                // printf("    - [FR sem_post] sem_file_reader\n");

                head = head->next;
                SEM_POST(sm.columnist_pw)
            }

            // printf("\n");
        }
    }

    rows_array_free(ras.input_rows, rows_allocated);

    // close all semaphores
    SEM_CLOSE_ALL(sm)

    return EXIT_SUCCESS;
}

/// @brief Child process to pass the justified rows to pages.
///
/// @param mem_map         the structure with shared memory pointer.
/// @param page_p          the structure with page properties.
///
/// @return the exit status.
///
int child_page_writer(shared_memory_map mem_map, semaphores_map sm, page_properties page_p)
{
    // wait
    // read shared memory
    SEM_WAIT(sm.columnist_pw)
    // copy shared memory
    size_t rows_written = *(mem_map.rows_written);
    // number of words in a row

    // printf("PW---- %ld\n", rows_written);

    SEM_POST(sm.page_writer)

    // used to receive a row from columnist process
    size_t words_in_row = 0;

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

    // local array of rows
    p_row *array_of_rows = rows_array_get(rows_written);

    // receiving rows from the columnist process
    for (size_t i = 0; i < rows_written; i++)
    {
        // pointer to current row
        p_row current_row = array_of_rows[i];

        // get the number of words in the current row
        SEM_WAIT(sm.columnist_pw)
        words_in_row = *(mem_map.words_allocated);
        // printf("Receiving row of %ld words: ", words_in_row);
        SEM_POST(sm.page_writer)

        // get rows in a row, sent one by one.
        for (size_t j = 0; j < words_in_row; j++)
        {
            SEM_WAIT(sm.columnist_pw)

            rows_array_add_word(current_row, mem_map.struct_word, *(mem_map.word_size));
            current_row->bytes += mem_map.struct_word->bytes;
            current_row->chars += mem_map.struct_word->chars;
            current_row->words++;
            // printf("%s", mem_map.struct_word->word);

            SEM_POST(sm.page_writer)
        }
    }

    // allocate a page
    // extra rows provided to avoid overflow
    size_t page_total_rows = (page_p.page_rows + BYTES_8) * pages_required;
    // allocation
    char **pages = pages_get(page_total_rows, page_p.page_columns);

    // write the array of rows into the page
    pages_write_rows(pages, array_of_rows, rows_written, pages_required, page_p);

    // pass to file writer the number of rows in pages to the file writer process
    // reuse rows written shared memory var
    SEM_WAIT(sm.file_writer)
    memcpy(mem_map.rows_written, &page_total_rows, sizeof(size_t));
    SEM_POST(sm.page_writer_fw)

    for (size_t i = 0; i < page_total_rows; i++)
    {
        SEM_WAIT(sm.file_writer)

        memset(mem_map.page_row, 0, page_p.page_columns + BYTES_64);
        memcpy(mem_map.page_row, pages[i], page_p.page_columns + BYTES_64);
        // printf("%s\n", pages[i]);

        SEM_POST(sm.page_writer_fw)
    }

    // release memory for the pages
    pages_free(pages, page_total_rows);

    // release memory for the array of rows
    rows_array_free(array_of_rows, rows_written);

    // close all semaphores
    SEM_CLOSE_ALL(sm)

    return EXIT_SUCCESS;
}

/// @brief Child process to write pages to a file.
///
/// @param input_file_name the name of the file where the words were read from, to generate output file name.
/// @param mem_map         the structure with shared memory pointer.
///
/// @return the exit status.
///
int child_file_writer(char *input_file_name, semaphores_map sm, shared_memory_map mem_map)
{
    CHECK_POINTER(input_file_name)

    // output file handle
    FILE *output_file;

    // page total rows
    // get the number of rows in pages form the page writer process
    SEM_WAIT(sm.page_writer_fw)

    size_t page_total_rows = 0;
    page_total_rows = *mem_map.rows_written;

    SEM_POST(sm.file_writer)

    // no overflow here
    char *output_file_name = calloc(strlen(input_file_name) + BYTES_16, sizeof(char));

    // create output file name
    strcat(output_file_name, "output.");
    strcat(output_file_name, input_file_name);

    // check if it's possiblee to open the output file
    OPEN_FILE(output_file, output_file_name, "w")

    for (size_t i = 0; i < page_total_rows; i++)
    {
        SEM_WAIT(sm.page_writer_fw)

        if (mem_map.page_row[0] != 0x00)
        {
            printf("%s\n", mem_map.page_row);
            fprintf(output_file, "%s\n", mem_map.page_row);
        }

        SEM_POST(sm.file_writer)
    }

    printf("\n[+] Output written to %s\n\n", output_file_name);

    // close output file handle
    fclose(output_file);

    // free memory for output file name
    free(output_file_name);

    // close all semaphores
    SEM_CLOSE_ALL(sm)

    return EXIT_SUCCESS;
}

/// @brief Handle childs in multiprocess mode.
///
/// @param pids the array with the pids of all childs.
///
void handle_childs(int pids[])
{
    // wait for proces children
    for (size_t i = 0; i < CHILDREN; i++)
    {

#ifdef _DEBUG
        printf("\e[95m[i] Parent waiting for child=%ld PID=%d\e[0m\n", i, pids[i]);
#endif

        int status = 0;

#ifdef _DEBUG
        int n_child = waitpid(pids[i], &status, 0);
        printf("\e[95m[i] Parent child=%ld exited: PID=%d, retcode=%d\e[0m\n", i, n_child, WEXITSTATUS(status));
#else
        waitpid(pids[i], &status, 0);
#endif
        // if the status is non zero
        // then kill other childs
        if (status)
        {
            // starting from the next child
            for (size_t j = i + 1; j < CHILDREN; j++)
            {
                kill(pids[j], SIGKILL);
#ifdef _DEBUG
                printf("\e[91m[i] Parent killed child=%ld PID=%d\e[0m\n", j, pids[j]);
#endif
            }

            break;
        }
    }
}