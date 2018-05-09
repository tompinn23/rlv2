#include "parser.h"
#include <stdlib.h>

char* read_line(FILE *fp)
{
	int c;
	int nch = 0;
	int size = 50;
	char *buf = malloc(size);
	if(!buf)
	{
		printf("Failed to allocate memory\n");
		exit(-1);
	}
	while ((c = fgetc(fp)) != '\n')
	{
		if (nch >= size - 1)
		{
			size += 20;
			buf = realloc(buf, size);
			if (!buf)
			{
				printf("Failed to allocate more memory\n");
				exit(-1);
			}
		}
		buf[nch++] = c;
	}
	buf[nch++] = '\n';
	buf[nch++] = '\0';
	return buf;
}

rl_room* parse_room(FILE* fp)
{
	char* line = read_line(fp);
	printf("%s", line);
	free(line);
	return NULL;
}