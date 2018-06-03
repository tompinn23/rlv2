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
#include "u-logging.h"

#include "time.h"
#include "string.h"
#include "stdlib.h"
#include "errno.h"

#define _CRT_SECURE_NO_WARNINGS

static FILE* fp = NULL;
static int init = 0;

void init_logging(const char* filename)
{
	errno = 0;
	fp = fopen(filename, "a");
	if (fp == NULL || errno != 0)
	{
		log_print("Failed to open log file: %s", strerror(errno));
	}
	init = 1;
}


void log_print(const char* format, ...)
{
	if (!init)
	{
		fprintf(stderr, "Call 'init_logging()' first.");
		return;
	}
	char* file = "<NULL>";
	int line = 0;
	time_t t = time(NULL);
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	char time_str[100];
	strftime(time_str, 100, "[%d/%b/%Y %H:%M:%S]", timeinfo);
	char* buf = NULL;
	if (file == NULL)
	{
		buf = calloc((strlen(time_str) + strlen(format) + 3), sizeof(char));
		snprintf(buf, (strlen(time_str) + strlen(format) + 3), "%s: %s", time_str, format);
	}
	else
	{
		buf = calloc((strlen(time_str) + strlen(format) + strlen(file) + 26), sizeof(char));
		snprintf(buf, (strlen(time_str) + strlen(format) + strlen(file) + 26), "%s: %s at %s:%d\n", time_str, format, file, line);
	}
	va_list args;
	va_start(args, format);
	vfprintf(stderr, buf, args);
	if (fp != NULL)
	{
		vfprintf(fp, buf, args);
		fflush(fp);
	}
	va_end(args);
	free(buf);
}