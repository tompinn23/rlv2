#pragma once

#include <stdio.h>
#include "generate.h"


long int parse_string(char* str);
char* parse_layout(FILE* fp, int rows, int cols);
rl_room* parse_room(FILE* fp);
rl_room** parse_rooms(FILE* fp);
