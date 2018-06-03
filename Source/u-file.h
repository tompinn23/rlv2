#pragma once

#include "generic.h"
#include <stdio.h>

typedef enum file_mode {
	FILE_READ = 0,
	FILE_WRITE = 1,
	FILE_APPEND = 2,
	FILE_RW = 3,

	FILE_MMAP = 8
} file_mode;

typedef enum file_type {
	TEXT_FILE = 0,
	BINARY_FILE = 1
} file_type;

//TODO: Error handling enum. 

typedef struct rl_file rl_file;

rl_file* file_open(char* filename, file_mode mode, file_type type);
void file_close(rl_file* file);

FILE* get_file_pointer(rl_file* file);

/* File IO */

int file_getc(rl_file* file);
size_t file_slurp(rl_file* file, char** buf);

/* Line IO */

bool file_readline(rl_file* file, char** buf);

