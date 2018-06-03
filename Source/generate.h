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
#pragma once

#include "map.h"

typedef struct rl_room {
	char* name;
	int width;
	int height;
	char *map;
} rl_room;

typedef map_t(rl_room*) map_room_t;



rl_room** get_rooms(int* max);
map_room_t get_room_map();

rl_room* alloc_room(char* name, int cols, int rows, char* map);
void free_room(rl_room* room);

char get_room_tile(rl_room* room, int x, int y);
