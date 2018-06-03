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
#pragma once

#include "generic.h"

#include "stdio.h"
#include "generate.h"
#include "u-file.h"

char* parse_layout(rl_file* file, int rows, int cols);
rl_room* parse_room(FILE* fp);
int parse_rooms(rl_file* file, map_room_t table);
