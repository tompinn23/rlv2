/*
rlv2
Copyright(C) 2018  Tom Pinnock

This program is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <https://www.gnu.org/licenses/>.
*/
#include "stdio.h"

#include "BearLibTerminal.h"
#include "parser.h"
#include "logging.h"



int main(int argc, char** argv)
{
	init_logging("rl.log");
	log_print("Hallo there!");

	char* buf = NULL;
	slurp("room.txt", &buf);

	//terminal_open();
  
    // Printing text
    //terminal_print(1, 1, "Hello, world!");
    //terminal_refresh();
	FILE* fp = fopen("room.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Failed to open file");
		exit(-1);
	}
	room_list* rooms = NULL;
	map_room_t table;
	map_init(&table);
	parse_rooms(fp, "room.txt", &rooms, &table);
	rl_room** rm = map_get(&table, "Room Uno");
	printf("%s\n", (*rm)->name);
	//terminal_refresh();
    //while (terminal_read() != TK_CLOSE);
	while (1);
    //terminal_close();
}