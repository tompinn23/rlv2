/*
rlv2
Copyright(C) 2018  Tom Pinnock

This program is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <https://www.gnu.org/licenses/>.
*/
#include "parser.h"

#include "errno.h"
#include <string.h>
#include <stdlib.h>
#include "logging.h"

static char* file_name = NULL;
static int line = 0;

int get_file_location()
{
	return line;
}

char* get_filename()
{
	return file_name;
}
/*
 You have to free the buffer as it is malloc in this function.
 It is up to the caller to free the buffer.
*/
size_t slurp(char* filename, char** buf)
{
	char* buffer = NULL;
	FILE* fp = fopen(filename, "rb");
	if (!fp)
	{
		log_print("Failed to open file: %s", filename);
		return 0;
	}
	fseek(fp, 0L, SEEK_END);
	size_t length = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	buffer = malloc(length + 1);
	if (!buffer)
	{
		log_print("Failed to allocate memory to read file: %s", filename);
		return 0;
	}
	fread(buffer, sizeof(char), length, fp);
	buffer[length] = '\0';
	printf("%s", buffer);
	*buf = buffer;
	return length;
}

void reset_file()
{
	file_name = NULL;
	line = 0;
}

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
	line++;
	return 1;
}

long int parse_string(char* str)
{
	errno = 0;
	char* temp;
	long int val = strtol(str, &temp, 10);
	if (temp == str || *temp != '\0' || ((val == LONG_MIN || val == LONG_MAX) && errno == ERANGE))
	{
		log_print("Could not parse number : %s", str);
	}
	return val;
}

char* parse_layout(FILE* fp, int rows, int cols)
{
	char* map = calloc((rows * cols), sizeof(char));
	char* line = malloc(sizeof(char) * cols + 1);

	for (int y = 0; y < rows; y++)
	{
		read_line(fp, line, cols + 1);
		for (int x = 0; x < cols; x++)
			map[(x * cols) + y] = line[x];
	}
	fseek(fp, -strlen(line), SEEK_CUR);
	free(line);
	return map;
}



rl_room* parse_room(FILE* fp)
{
	char* name = NULL;
	int rows = 0;
	int cols = 0;
	char* map = NULL;
	int res = 0;
	char* line = malloc(sizeof(char) * 50);
	res = read_line(fp, line, 50);
	while (res == 1)
	{
		if (strstr(line, "name:") == line)
		{
			name = strdup(line + 5);
			if (name == "")
				log_print("%s", "Name cannot be empty.");
		}
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

int parse_rooms(FILE * fp, char* filename, room_list** list, map_room_t map)
{
	file_name = filename;
	int length = 0;
	int max = 20;
	*list = malloc(sizeof(room_list));
	room_list* ptr = *list;
	rl_room** rooms = malloc(max * sizeof(rl_room*));
	if (rooms == NULL)
	{
		reset_file();
		return -1;
	}
	do
	{
		rl_room* room = parse_room(fp);
		if (length == max)
		{
			max += 10;
			rl_room** tmp = realloc(rooms, max);
			if (tmp == NULL)
			{
				free(rooms);
				reset_file();
				return -1;
			}
		}
		if (room == NULL)
			continue;
		map_set(&map, room->name, room);
		rooms[length] = room;
		length++;
	} while (!feof(fp));
	ptr->roomNum = length;
	ptr->rooms = rooms;
	reset_file();
	return 0;
}
