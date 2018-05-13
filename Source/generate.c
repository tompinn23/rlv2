#include "generate.h"
#include "stdlib.h"

rl_room* alloc_room(char* name, int cols, int rows, char* map)
{
	rl_room* ptr = malloc(sizeof(rl_room));
	ptr->name = name;
	ptr->rows = rows;
	ptr->cols = cols;
	ptr->map = map;
	return ptr;
}

void free_room(rl_room* room)
{
	free(room->name);
	free(room->map);
	free(room);
}

char get_room_tile(rl_room * room, int x, int y)
{
	return room->map[x * room->cols + y];
}

char* generate_map()
{

}