#pragma once

#include "stdlib.h"

void* mem_alloc(size_t size);
void* mem_zalloc(size_t size);

void* mem_realloc(void* ptr, size_t size);