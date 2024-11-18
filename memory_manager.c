#include <stdlib.h>
#include "memory_manager.h"

size_t allocated_memory = 0; 
Allocation *allocations = NULL;  
size_t allocations_count = 0;  

void* my_malloc(size_t size) {
    void* ptr = malloc(size);
    #ifdef DEBUG
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed: size=%zu\n", size);
    } else {
        fprintf(stderr, "Allocated memory: size=%zu at %p\n", size, ptr);
    }
    #endif

    if (ptr != NULL) {
        allocated_memory += size;

        allocations = realloc(allocations, sizeof(Allocation) * (allocations_count + 1));
        allocations[allocations_count].ptr = ptr;
        allocations[allocations_count].size = size;
        allocations_count++;
    }

    #ifdef DEBUG
    fprintf(stderr, "Debug: Inside my_malloc. Size: %zu\n", size);
    #endif

    return ptr;
}

void my_free(void* ptr) {
    #ifdef DEBUG
    fprintf(stderr, "Freeing memory at %p\n", ptr);
    #endif

    for (size_t i = 0; i < allocations_count; i++) {
        if (allocations[i].ptr == ptr) {
            allocated_memory -= allocations[i].size;
            free(ptr);
            for (size_t j = i; j < allocations_count - 1; j++) {
                allocations[j] = allocations[j + 1];
            }
            allocations_count--;
            allocations = realloc(allocations, sizeof(Allocation) * allocations_count);
            break;
        }
    }
}



void* my_realloc(void* ptr, size_t new_size) {
    void* new_ptr = realloc(ptr, new_size);
    #ifdef DEBUG
    if (new_ptr == NULL) {
        fprintf(stderr, "Memory reallocation failed: new_size=%zu\n", new_size);
    } else {
        fprintf(stderr, "Reallocated memory: new_size=%zu at %p\n", new_size, new_ptr);
    }
    #endif
    for (size_t i = 0; i < allocations_count; ++i) {
        if (allocations[i].ptr == ptr) {
            allocated_memory = allocated_memory - allocations[i].size + new_size;

            allocations[i].ptr = new_ptr;
            allocations[i].size = new_size;
            break;
        }
    }

    return new_ptr;
}

void check_memory_leaks() {
    #ifdef DEBUG
    if (allocated_memory > 0) {
        fprintf(stderr, "Memory leak detected: %zu bytes still allocated.\n", allocated_memory);
    } else {
        fprintf(stderr, "No memory leaks detected.\n");
    }
    #endif
}
