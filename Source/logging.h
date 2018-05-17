#pragma once

#include "stdio.h"
#include "stdarg.h"

void set_fp(FILE* file);
void log_print(const char* format, ...);