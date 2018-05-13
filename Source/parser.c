#include "parser.h"

#include "errno.h"
#include <string.h>
#include <stdlib.h>

int read_line(FILE* fp, char* buf, int max)
{
	int length = 0;
	int ch = fgetc(fp);
	while ((ch != EOF) && (ch != '\n'))
	{
		if (length == max)
		{
			max += 20;
			buf = realloc(buf, max);
		}
		buf[length] = ch;
		length++;
		ch = fgetc(fp);
	}
	buf[length] = '\0';
	if (ch == EOF && buf[0] == '\0')
	{
		return 0;
	}

	return 1;
}

long int parse_string(char* str)
{
	errno = 0;
	char* temp;
	long int val = strtol(str, &temp, 10);
	if (temp == str || *temp != '\0' || ((val == LONG_MIN || val == LONG_MAX) && errno == ERANGE))
	{
		fprintf(stderr, "Could not parse number: %s", str);
	}
	return val;
}

char* parse_layout(FILE* fp, int rows, int cols)
{
	char* map = calloc((rows * cols), sizeof(char));
	char* line = malloc(sizeof(char) * cols + 1);
	read_line(fp, line, cols + 1);
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			map[(x * cols) + y] = line[x];
		}
		read_line(fp, line, cols + 1);
	}
	fseek(fp, -strlen(line), SEEK_CUR);
	map[rows * cols] = '\0';
	free(line);
	return map;
}



rl_room* parse_room(FILE* fp)
{
	char* name;
	int rows;
	int cols;
	char* map;
	int res;
	char* line = malloc(sizeof(char) * 50);
	res = read_line(fp, line, 50);
	while (res == 1)
	{
		if (strstr(line, "name:") == line)
			name = strdup(line + 5);
		else if (strstr(line, "rows:") == line)
		{
			rows = parse_string(line + 5);
		}
		else if (strstr(line, "cols:") == line)
		{
			cols = parse_string(line + 5);
		}
		else if (strstr(line, "P:") == line)
		{
			map = parse_layout(fp, rows, cols);
		}
		else if (strstr(line, ":P") == line)
		{
			break;
		}
		res = read_line(fp, line, 50);
	}
	free(line);
	return alloc_room(name, cols, rows, map);
}

rl_room ** parse_rooms(FILE * fp)
{
	return NULL;
}
