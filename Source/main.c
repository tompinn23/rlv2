#include "stdio.h"

#include "BearLibTerminal.h"
#include "parser.h"
#include "logging.h"

int main(int argc, char** argv)
{
	terminal_open();
  
    // Printing text
    terminal_print(1, 1, "Hello, world!");
    terminal_refresh();
	FILE* fp = fopen("room.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Failed to open file");
		exit(-1);
	}
	log_print("help");
	room_list* rooms = NULL;
	map_room_t table;
	map_init(&table);
	parse_rooms(fp, "room.txt", &rooms, &table);
	rl_room** rm = map_get(&table, "Room Uno");
	printf("%s\n", (*rm)->name);
	terminal_refresh();
    while (terminal_read() != TK_CLOSE);
  
    terminal_close();
}