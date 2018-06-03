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
#include "jsmn.h"

#include "u-logging.h"
#include "u-mem.h"
#include "u-file.h"
#include "u-util.h"
#include "generate.h"

int main(int argc, char** argv)
{
	init_logging("rl.log");
	log_print("Hallo there!");

	//terminal_open();
  
    // Printing text
    //terminal_print(1, 1, "Hello, world!");
    //terminal_refresh();
	//terminal_refresh();
    //while (terminal_read() != TK_CLOSE);
    //terminal_close();
	rl_file* fl = file_open("rooms.json", FILE_READ, TEXT_FILE);
	uint8_t* text = NULL;
	size_t bytes = file_slurp(fl, &text);
	jsmn_parser parser;
	jsmn_init(&parser);
	jsmntok_t* toks = mem_alloc(256 * sizeof(jsmntok_t));
	int r = jsmn_parse(&parser, text, bytes, toks, 256);
	if (r < 0)
		quit("Failed to parse json.\n Is this a valid file.\n", EXIT_FAILURE);
	if (r < 1 || toks[0].type != JSMN_OBJECT)
		quit("Expected a top level room object.\n", EXIT_FAILURE);
	char* name = NULL;
	int width = 0;
	int height = 0;
	for (int i = 1; i < r; i++)
	{
		log_print("TOK TYPE: %d", toks[i].type);
		//printf("%.*s\n", toks[i].end - toks[i].start, text + toks[i].start);
		if (toks[1].type == JSMN_STRING)
		{

		}
	}
}