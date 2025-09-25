#ifndef MONITOR_MEMORIA_H
#define MONITOR_MEMORIA_H

#include <stdlib.h>

extern size_t current_mem;
extern size_t peak_mem;

void* my_malloc(size_t size);
void my_free(void* ptr, size_t size);

#endif
