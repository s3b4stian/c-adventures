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
#include <errno.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>

#include "columns.h"
#include "process_single.h"
#include "process_multi.h"

// semaphores
extern const char *name_sem_file_reader;
extern const char *name_sem_columnist;
extern const char *name_sem_columnist_pw;
extern const char *name_sem_page_writer;
extern const char *name_sem_page_writer_fw;
extern const char *name_sem_file_writer;

/// @brief Print program options
void print_options()
{
    printf("\nusage:\n");
    printf("\t./colonnade -f input.txt -c 30\n\n");
    printf("options [default value]:\n");
    printf("\t-f    indicates the input file\n");
    printf("\t-c    [30]  indicates the width of a column in chars\n");
    printf("\t-n    [2]   indicates the number of columns per page\n");
    printf("\t-s    [2]   indicates the space between columns\n");
    printf("\t-r    [40]  indicates the number of rows for a column/per page\n");
    printf("\t-m    [nil] indicates the use of multi processing\n\n");
}

/**
 * Main.
 *
 * This program takes a text file in input and return it formatted in columns.
 *
 * compile:
 *      make
 *
 * compile debug:
 *      make debug
 *
 * compile clean:
 *      make clean
 *
 * usage:
 *      ./colonnade -f input.txt -c 30 -m
 *
 * options:
 *      -f     indicates the input file
 *      -c     indicates the width of a column in chars
 *      -n     indicates the number of columns per page
 *      -s     indicates the space between columns
 *      -r     indicates the number of rows for a column/per page
 *      -m     indicates the use of multi processing
 *
 * memory check:
 *      valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./colonnade -f input.txt -c 30 -n 3
 */
int main(int argc, char *argv[])
{
#ifdef _DEBUG
    printf("\e[92m[i] Compiled in DEBUG mode.\e[0m\n");
#endif

    // options default

    //-f input file name, usefull for the name of the output file
    char *input_file_name = NULL;

    //-c maximun chars in a column
    size_t column_size = 30;

    //-n columns per page
    size_t columns_per_page = 2;

    //-s space between column expressed in chars
    size_t columns_spacing = 4;

    //-r rows for page
    size_t page_rows = 30;

    //-m multi processing
    size_t multi_processing = false;

    // if no options
    if (argc == 1)
    {
        print_options();
        exit(EXIT_FAILURE);
    }

    // option
    int opt;
    // get options
    while ((opt = getopt(argc, argv, ":f:c:n:s:r:m")) != -1)
    {
        switch (opt)
        {
        case 'f':
            input_file_name = optarg;
            break;
        case 'c':
            column_size = strtol(optarg, NULL, 10);
            break;
        case 'n':
            columns_per_page = strtol(optarg, NULL, 10);
            break;
        case 's':
            columns_spacing = strtol(optarg, NULL, 10);
            break;
        case 'r':
            page_rows = strtol(optarg, NULL, 10);
            break;
        case 'm':
            multi_processing = true;
            break;
        case ':':
            printf("[!] Option -%c needs a value.\n", optopt);
            break;
        case '?':
            printf("[!] Unknown option [-%c].\n", optopt);
            print_options();
            exit(EXIT_FAILURE);
            break;
        }
    }

    // page columns, chars in a row for final page
    // thinking as page[y][x] is the max value for the x
    // here columns are calculated using below formula
    size_t page_columns = (column_size * columns_per_page) + (columns_spacing * (columns_per_page - 1));

    // page properties grouping
    page_properties pp = {
        .column_size = column_size,
        .columns_per_page = columns_per_page,
        .columns_spacing = columns_spacing,
        .page_rows = page_rows,
        .page_columns = page_columns,
    };

    // solution selected is shard memory and semaphores
    // because I want go deep and it sems the most difficult solution compared to pipes, named pipes and other interprocess communication methods
    // socket excluded because this program runs locally, no netword needed
    if (multi_processing)
    {
        // weird things happens if a process start is delayed
#ifdef _DEBUG
        printf("\e[92m[+] Colonnade in multi processing mode\e[0m\n");
#endif

        // shared memory
        void *shmem_st_word = shared_memory_get(sizeof(word));
        void *shmem_word = shared_memory_get(BYTES_128);
        void *shmem_word_size = shared_memory_get(sizeof(size_t));
        void *shmem_words_allocated = shared_memory_get(sizeof(size_t));
        void *shmem_rows_written = shared_memory_get(sizeof(size_t));
        // + BYTES_64 because in function pages_get in columns.c extra space is allocated
        void *shmem_page_row = shared_memory_get(page_columns + BYTES_64);

        CHECK_POINTER(shmem_st_word)
        CHECK_POINTER(shmem_word)
        CHECK_POINTER(shmem_word_size)
        CHECK_POINTER(shmem_words_allocated)
        CHECK_POINTER(shmem_rows_written)
        CHECK_POINTER(shmem_page_row)

        shared_memory_map shmem_map = (shared_memory_map){
            .struct_word = (p_word)shmem_st_word,
            .word_size = (size_t *)shmem_word,
            .word = (char *)shmem_word_size,
            .words_allocated = (size_t *)shmem_words_allocated,
            .rows_written = (size_t *)shmem_rows_written,
            .page_row = (char *)shmem_page_row};

        // clean named semaphores
        sem_unlink(name_sem_file_reader);
        sem_unlink(name_sem_columnist);
        sem_unlink(name_sem_columnist_pw);
        sem_unlink(name_sem_page_writer);
        sem_unlink(name_sem_page_writer_fw);
        sem_unlink(name_sem_file_writer);

        // semaphores between 1st and 2nd processes
        sem_t *s_file_reader = sem_open(name_sem_file_reader, O_CREAT, 0600, 0);
        sem_t *s_columnist = sem_open(name_sem_columnist, O_CREAT, 0600, 1);
        // semaphores between 2nd and 3rd processes
        sem_t *s_columnist_pw = sem_open(name_sem_columnist_pw, O_CREAT, 0600, 0);
        sem_t *s_page_writer = sem_open(name_sem_page_writer, O_CREAT, 0600, 1);
        // semaphores between 3rd and 4th processes
        sem_t *s_page_writer_fw = sem_open(name_sem_page_writer_fw, O_CREAT, 0600, 0);
        sem_t *s_file_writer = sem_open(name_sem_file_writer, O_CREAT, 0600, 1);

        SEM_CHECK(s_file_reader)
        SEM_CHECK(s_columnist)
        SEM_CHECK(s_columnist_pw)
        SEM_CHECK(s_page_writer)
        SEM_CHECK(s_page_writer_fw)
        SEM_CHECK(s_file_writer)

        semaphores_map sem = (semaphores_map){
            .file_reader = s_file_reader,
            .columnist = s_columnist,
            .columnist_pw = s_columnist_pw,
            .page_writer = s_page_writer,
            .page_writer_fw = s_page_writer_fw,
            .file_writer = s_file_writer};

        // child counter
        int child;
        // array for store the pid of every children
        int pids[CHILDREN];

        // 1 file reader
        // 2 columnist
        // 3 page writer
        // 4 file writer
        for (child = 0; child < CHILDREN; child++)
        {
            // fork the current process
            int pid = fork();

            // if failure
            if (pid == -1)
            {
#ifdef _DEBUG
                fprintf(stderr, "[!] Fork failed: %s\n", strerror(errno));
#endif

                return EXIT_FAILURE;
            }
            else if (pid == IS_CHILD)
            {
                switch (child)
                {
                case CHILD_FILE_READER:
#ifdef _DEBUG
                    printf("\e[92m[i] Start File Reader as child=%d PID=%d\e[0m\n", child, getpid());
#endif
                    return child_file_reader(input_file_name, shmem_map, sem, pp);

                    break;
                case CHILD_COLUMNIST:
#ifdef _DEBUG
                    printf("\e[92m[i] Start Columnist as child=%d PID=%d\e[0m\n", child, getpid());
#endif
                    return child_columnist(shmem_map, sem, pp);

                    break;
                case CHILD_PAGE_WRITER:
#ifdef _DEBUG
                    printf("\e[92m[i] Start Page writer as child=%d PID=%d\e[0m\n", child, getpid());
#endif
                    return child_page_writer(shmem_map, sem, pp);

                    break;
                case CHILD_FILE_WRITER:
#ifdef _DEBUG
                    printf("\e[92m[i] Start File writer as child=%d PID=%d\e[0m\n", child, getpid());
#endif
                    return child_file_writer(input_file_name, sem, shmem_map);

                    break;

                    // if the program fow arrive here
                    // something went wrong
                default:

#ifdef _DEBUG
                    fprintf(stderr, "\e[92m[!] Something has gone really wrong\e[0m\n");
#endif
                    return EXIT_FAILURE;
                }
            }

            pids[child] = pid;
        }

        // check the end status of childs
        handle_childs(pids);

        // close all semaphores
        SEM_CLOSE_ALL(sem)

        // unmap shared memori previous allocated
        munmap(shmem_st_word, sizeof(word));
        munmap(shmem_word, BYTES_128);
        munmap(shmem_word_size, sizeof(size_t));
        munmap(shmem_words_allocated, sizeof(size_t));
        munmap(shmem_rows_written, sizeof(size_t));
        munmap(shmem_page_row, page_columns + BYTES_64);

        return EXIT_SUCCESS;
    }
    else
    {
        return single_process(input_file_name, pp);
    }
}
