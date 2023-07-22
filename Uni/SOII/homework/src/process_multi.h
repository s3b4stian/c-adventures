/**
 * Copyright 2023 Sebastian Rapetti
 *
 * Part of the program Colonnade.
 * License - MIT
 */

#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <semaphore.h>
#include <errno.h>
#include "columns.h"

#ifndef _PROCESS_MULTI_H
#define _PROCESS_MULTI_H 1

// declared one more time here to avoid an error with ubuntu 23.04
#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS 0x20 /* Don't use a file.  */
#define MAP_ANON MAP_ANONYMOUS
#endif

#define CHILDREN 4

#define IS_CHILD 0
#define CHILD_FILE_READER 0
#define CHILD_COLUMNIST 1
#define CHILD_PAGE_WRITER 2
#define CHILD_FILE_WRITER 3

#define SEM_CHECK(s)                                                                                                         \
    if (s == SEM_FAILED)                                                                                                     \
    {                                                                                                                        \
        fprintf(stderr, "\e[91m[sem_open] failed at line %d in file %s! error number %d\e[0m\n", __LINE__, __FILE__, errno); \
        return EXIT_FAILURE;                                                                                                 \
    }
#define SEM_WAIT(s)                                                                                                          \
    if (sem_wait(s) < 0)                                                                                                     \
    {                                                                                                                        \
        fprintf(stderr, "\e[91m[sem_wait] failed at line %d in file %s! error number %d\e[0m\n", __LINE__, __FILE__, errno); \
        return EXIT_FAILURE;                                                                                                 \
    }
#define SEM_POST(s)                                                                                                          \
    if (sem_post(s) < 0)                                                                                                     \
    {                                                                                                                        \
        fprintf(stderr, "\e[91m[sem_post] failed at line %d in file %s! error number %d\e[0m\n", __LINE__, __FILE__, errno); \
        return EXIT_FAILURE;                                                                                                 \
    }
#define SEM_CLOSE(s)                                                                                                          \
    if (sem_close(s) != 0)                                                                                                    \
    {                                                                                                                         \
        fprintf(stderr, "\e[91m[sem_close] failed at line %d in file %s! error number %d\e[0m\n", __LINE__, __FILE__, errno); \
        return EXIT_FAILURE;                                                                                                  \
    }
#define SEM_UNLINK(s)                                                                                                          \
    if (sem_unlink(s) < 0)                                                                                                     \
    {                                                                                                                          \
        fprintf(stderr, "\e[91m[sem_unlink] failed at line %d in file %s! error number %d\e[0m\n", __LINE__, __FILE__, errno); \
        return EXIT_FAILURE;                                                                                                   \
    }

#define SEM_CLOSE_ALL(s)        \
    SEM_CLOSE(s.file_reader)    \
    SEM_CLOSE(s.columnist)      \
    SEM_CLOSE(s.columnist_pw)   \
    SEM_CLOSE(s.page_writer)    \
    SEM_CLOSE(s.page_writer_fw) \
    SEM_CLOSE(s.file_writer)

// groups the pointers to shared memory
// used to avoid function with 2*10^78 paramethers
typedef struct _shared_memory_map
{
    p_word struct_word;
    size_t *word_size;
    char *word;
    size_t *words_allocated;
    size_t *rows_written;
    char *page_row;

} shared_memory_map;

typedef struct _semaphores_map
{
    sem_t *file_reader;
    sem_t *columnist;
    sem_t *columnist_pw;
    sem_t *page_writer;
    sem_t *page_writer_fw;
    sem_t *file_writer;
} semaphores_map;

/// @brief A wrapper to mmap function.
///
/// @param size the number of bytes required.
///
/// @return the pointer to shared memory-
///
void *shared_memory_get(size_t size);

/// @brief Child process to read file and create array of word.
//
/// @param input_file_name the name file to read words.
/// @param mem_map         the structure with shared memory pointer.
/// @param page_p          the structure with page properties.
///
/// @return the exit status.
///
int child_file_reader(char *input_file_name, shared_memory_map mem_map, semaphores_map sm, page_properties page_p);

/// @brief Child process to create array of justified rows.
///
/// @param mem_map         the structure with shared memory pointer.
/// @param page_p          the structure with page properties.
///
/// @return the exit status.
///
int child_columnist(shared_memory_map mem_map, semaphores_map sm, page_properties page_p);

/// @brief Child process to pass the justified rows to pages.
///
/// @param mem_map         the structure with shared memory pointer.
/// @param page_p          the structure with page properties.
///
/// @return the exit status.
///
int child_page_writer(shared_memory_map mem_map, semaphores_map sm, page_properties page_p);

/// @brief Child process to write pages to a file.
///
/// @param input_file_name the name of the file where the words were read from, to generate output file name.
/// @param mem_map         the structure with shared memory pointer.
///
/// @return the exit status.
///
int child_file_writer(char *input_file_name, semaphores_map sm, shared_memory_map mem_map);

/// @brief Handle childs in multiprocess mode.
///
/// @param pids the array with the pids of all childs.
///
void handle_childs(int pids[]);

#endif /* process_multi.h */