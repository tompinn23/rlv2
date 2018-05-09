#pragma once

#include <stdio.h>

typedef struct {
	char* name;
	char* id;
	int col;
	int row;
	char *map;
} rl_room;


rl_room* parse_room(FILE* fp);