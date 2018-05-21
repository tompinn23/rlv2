#include "u-file.h"


typedef struct rl_file {
	char* filename;
	FILE* fp;
	file_mode mode;
	unsigned long lineno;
	unsigned int colno;
} rl_file;

rl_file * file_open(const char * filename, file_mode mode)
{
	mem
}
