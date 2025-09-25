#include "monitor_memoria.h"

size_t current_mem = 0;
size_t peak_mem = 0;

void* my_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr != NULL) {
        current_mem += size;
        if (current_mem > peak_mem) {
            peak_mem = current_mem;
        }
    }
    return ptr;
}

void my_free(void* ptr, size_t size) {
    if (ptr != NULL) {
        current_mem -= size;
        free(ptr);
    }
}
