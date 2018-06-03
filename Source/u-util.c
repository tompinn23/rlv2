#include "u-util.h"
#include "u-logging.h"

#include <stdlib.h>
void quit(const char* str, int code)
{
	log_print("Quitting with error code: %d because %s", code, str);
	exit(code);
}