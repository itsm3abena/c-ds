#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stdio.h>

typedef struct {
    void *ptr;
    size_t size;
} Allocation;

extern size_t allocated_memory; 
extern Allocation *allocations;  
extern size_t allocations_count;  

void* my_realloc(void* ptr, size_t new_size);
void check_memory_leaks(void);

#endif // MEMORY_MANAGER_H
