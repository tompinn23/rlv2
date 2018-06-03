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

#include "generate.h"
#include "stdlib.h"
#include "stdio.h"
#include "u-mem.h"


static map_room_t _room_map;

rl_room* alloc_room(char* name, int cols, int rows, char* map)
{
	rl_room* ptr = mem_alloc(sizeof(rl_room));
	if (name == "" || name == NULL)
	{
		fprintf(stderr, "Name Cannot be null!");
		return NULL;
	}
	if (cols == 0)
	{
		fprintf(stderr, "Columns cannot be 0!");
		return NULL;
	}
	
	ptr->name = name;
	ptr->height = rows;
	ptr->width = cols;
	ptr->map = map;
	return ptr;
}

void free_room(rl_room* room)
{
	mem_free(room->name);
	mem_free(room->map);
	mem_free(room);
}


char get_room_tile(rl_room * room, int x, int y)
{
	return room->map[(x * room->width) + y];
}

char* generate_map()
{
	return NULL;
}