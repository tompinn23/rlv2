#include "u-file.h"

#include "u-logging.h"
#include "u-util.h"

typedef struct rl_file {
	char* filename;
	FILE* fp;
	file_mode mode;
	file_type type;
	unsigned long lineno;
	unsigned int colno;
	bool eof;
} rl_file;

/*
 * File must be closed with file_close() 
 */
rl_file * file_open(char * filename, file_mode mode, file_type type)
{
	rl_file* f = mem_zalloc(sizeof(rl_file));
	f->filename = filename;
	f->mode = mode;
	f->type = type;
	f->lineno = 0;
	f->colno = 0;
	f->eof = false;
	switch (mode)
	{
	case FILE_READ:
		f->fp = fopen(filename, "rb");
		break;
	case FILE_WRITE:
		f->fp = fopen(filename, "wb");
		break;
	case FILE_APPEND:
		f->fp = fopen(filename, "ab");
		break;
	case FILE_RW:
		f->fp = fopen(filename, "rb+");
		break;
	case FILE_MMAP:
		quit("Unimplemented", EXIT_FAILURE);
		break;
	default:
		break;
	}
	if (!(f->fp))
	{
		log_print("Failed to open file! %s", filename);
		return NULL;
	}
	return f;
}


void file_close(rl_file * file)
{
	fclose(file->fp);
	mem_free(file);
}

int file_getc(rl_file* file)
{
	int ch = fgetc(file->fp);
	if (ch == EOF)
		file->eof = true;
	file->colno++;
	if (ch == '\n')
	{
		file->lineno++;
		file->colno = 0;
	}
	return ch;
}

size_t file_slurp(rl_file* file, char** buf)
{
	fseek(file->fp, 0, SEEK_END);
	size_t length = ftell(file->fp);
	fseek(file->fp, 0, SEEK_SET);
	char* buffer = mem_alloc(length + 1);
	fread(buffer, sizeof(char), length, file->fp);
	buffer[length] = '\0';
	(*buf) = buffer;
	return length;
}

bool file_readline(rl_file* file, char** buf)
{
	int max = 50;
	char* buffer = mem_alloc(max);
	int length = 0;
	int ch = fgetc(file->fp);
	while ((ch != EOF) && (ch != '\n'))
	{
		if (length == max)
		{
			max += 20;
			buffer = mem_realloc(buffer, max);
		}
		buffer[length] = ch;
		length++;
		ch = fgetc(file->fp);
	}
	buffer[length] = '\0';
	if (ch == EOF && buffer[0] == '\0')
	{
		return false;
	}
	file->lineno++;
	(*buf) = buffer;
	return true;
}

FILE* get_file_pointer(rl_file* file)
{
	return file->fp;
}