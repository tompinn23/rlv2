#pragma once

typedef struct {
	char* name;
	int cols;
	int rows;
	char *map;
} rl_room;

rl_room* alloc_room(char* name, int cols, int rows, char* map);
void free_room(rl_room* room);

char get_room_tile(rl_room* room, int x, int y);
