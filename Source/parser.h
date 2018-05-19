#pragma once

#include "stdio.h"
#include "generate.h"

typedef struct {
	char* filename;
	int line;
} file_info;

int get_file_location();
char* get_filename();
char* parse_layout(FILE* fp, int rows, int cols);
rl_room* parse_room(FILE* fp);
int parse_rooms(FILE* fp, char* name, room_list** list, map_room_t** table);
