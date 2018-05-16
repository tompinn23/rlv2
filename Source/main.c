#include <stdio.h>

#include "BearLibTerminal.h"
#include "parser.h"

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
	room_list* rooms = parse_rooms(fp);
	rl_room* rm = rooms->rooms[0];
	for (int i = 0; i < rm->width; i++)
	{
		for (int j = 0; j < rm->height; j++)
		{
			terminal_put(i, j, get_room_tile(rm, i, j));
		}
	}
    // Wait until user close the window
	terminal_refresh();
	terminal_read();
	terminal_clear();
	rm = rooms->rooms[1];
	for (int j = 0; j < rm->height; j++)
	{
		for (int i = 0; i < rm->width; i++)
		{
			terminal_put(i, j, get_room_tile(rm, i, j));
			terminal_refresh();
		}
	}
	terminal_refresh();
    while (terminal_read() != TK_CLOSE);
  
    terminal_close();
}