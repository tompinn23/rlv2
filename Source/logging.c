#include "logging.h"
#include "time.h"
#include "string.h"
#include "stdlib.h"

void log_print(const char* format, ...)
{

	time_t t = time(NULL);
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	char time_str[100];
	strftime(time_str, 100, "[%d/%b/%Y %H:%M:%S]", timeinfo);
	char* buf = calloc((strlen(time_str) + strlen(format) + 1), sizeof(char));
	sprintf(buf, "%s: %s", time_str, format);
	va_list args;
	va_format(args, format);
	vprintf(format, args);
	va_end(args);
}