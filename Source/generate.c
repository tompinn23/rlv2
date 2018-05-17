#include "generate.h"

#include "stdlib.h"
#include "stdio.h"

rl_room* alloc_room(char* name, int cols, int rows, char* map)
{
	rl_room* ptr = malloc(sizeof(rl_room));
	if (ptr == NULL)
	{
		fprintf(stderr, "Failed to allocate Room!");
		return NULL;
	}
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
	free(room->name);
	free(room->map);
	free(room);
}

void free_rooms_list(room_list* rooms)
{
	for (int i = 0; i < rooms->roomNum; i++)
	{
		free_room(rooms->rooms[i]);
	}
	free(rooms);
}

char get_room_tile(rl_room * room, int x, int y)
{
	return room->map[(x * room->width) + y];
}

char* generate_map()
{

}