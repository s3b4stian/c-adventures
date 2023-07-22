/**
 * Copyright 2023 Sebastian Rapetti
 *
 * Part of the program Colonnade.
 * License - MIT
 */

#include <stdlib.h>
#include <stdbool.h>
#include "columns.h"

#ifndef _PROCESS_SINGLE_H
#define _PROCESS_SINGLE_H 1

/// @brief Execute the program in single process manner.
///
/// @param input_file_name the name of the file to manipulate.
/// @param page_p          the properties of the page.
///
/// @return status code, 0 success other failure.
///
int single_process(char *input_file_name, page_properties page_p);

#endif /* process_single.h */