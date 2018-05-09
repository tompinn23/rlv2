#include <stdio.h>

#include "BearLibTerminal.h"
#include "parser.h"

int main(int argc, char** argv)
{
	terminal_open();
  
    // Printing text
    terminal_print(1, 1, "Hello, world!");
    terminal_refresh();
    // Wait until user close the window
	FILE* fp = fopen("room.txt", "r");
	if (!fp)
	{
		printf("Failed to open file!\n");
	}
	parse_room(fp);
	printf("Hello\n");
    while (terminal_read() != TK_CLOSE);
  
    terminal_close();
}