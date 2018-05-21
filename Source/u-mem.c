#include "u-mem.h"
#include "logging.h"
#include "string.h"

//#define POISON_ALLOC

void * mem_alloc(size_t size)
{
	if (size == 0) return NULL;
	void* mem = malloc(size);
	if (!mem)
	{
		quit("Out of memory!.", EXIT_FAILURE);
	}
#if defined(POISON_ALLOC)
	memset(mem, 0xA5, size);
#endif
	return mem;
}

void * mem_zalloc(size_t size)
{
	void* mem = mem_alloc(size);
	if (len)
	{
		memset(mem, 0, size);
	}
	return mem;
}

//TODO: Finish memory functions.

void * mem_realloc(void * ptr, size_t size)
{
	if (!ptr)
	{
		if (size == 0)
		{
			free(ptr);
			return NULL;
		}
	}
}

void * mem_free(void * ptr)
{

}