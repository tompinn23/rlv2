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
	rl_room* rm = parse_room(fp);
	for (int i = 0; i < rm->cols; i++)
	{
		for (int j = 0; j < rm->rows; j++)
		{
			terminal_put(i, j, get_room_tile(rm, i, j));
		}
	}
    // Wait until user close the window
	terminal_refresh();
    while (terminal_read() != TK_CLOSE);
  
    terminal_close();
}