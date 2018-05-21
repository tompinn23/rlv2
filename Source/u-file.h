#pragma once

#include "stdbool.h"

typedef enum file_mode {
	FILE_TREAD = 0,
	FILE_TRWITE = 1,
	FILE_TAPPEND = 2,
	FILE_TRW = 3,

	FILE_BREAD = 4,
	FILE_BWRITE = 5,
	FILE_BAPPEND = 6,
	FILE_BRW = 7,

	FILE_MMAP = 8
} file_mode;

//TODO: Error handling enum. 

typedef rl_file rl_file;

rl_file* file_open(const char* filename, file_mode mode);


