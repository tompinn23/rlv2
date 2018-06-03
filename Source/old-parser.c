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
				log_print("Name cannot be empty.");
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

map_room_t parse_rooms(rl_file* file)
{

}
