#pragma once

#include "map.h"

typedef struct {
	char* name;
	int width;
	int height;
	char *map;
} rl_room;

typedef map_t(rl_room*) map_room_t;

typedef struct {
	int roomNum;
	rl_room** rooms;
} room_list;


rl_room* alloc_room(char* name, int cols, int rows, char* map);
void free_room(rl_room* room);
void free_room_list(room_list* rooms);

char get_room_tile(rl_room* room, int x, int y);
