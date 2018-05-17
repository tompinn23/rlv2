#include "parser.h"

#include "errno.h"
#include <string.h>
#include <stdlib.h>

static char* last_name = "";
static char* file_name = "";
static int line = 0;

int get_file_location()
{
	return line;
}

char* get_filename()
{
	return file_name;
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
				log_print("%s", "Name cannot be empty.")
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
		return 0;
	}
	while (!feof(fp))
	{
		rl_room* room = parse_room(fp);
		if (length == max)
		{
			max += 10;
			rl_room** tmp = realloc(rooms, max);
			if (tmp == NULL)
			{
				free(rooms);
				return 0;
			}
		}
		map_set(&map, room->name, room);
		rooms[length] = room;
		length++;
	}
	ptr->roomNum = length;
	ptr->rooms = rooms;
	return 1;
}
