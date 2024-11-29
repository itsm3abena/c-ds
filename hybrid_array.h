#ifndef HYBRID_ARRAY_H
#define HYBRID_ARRAY_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG

// Memory Manager
typedef struct {
    void *ptr;
    size_t size;
} Allocation;

size_t allocated_memory = 0;       
Allocation *allocations = NULL;   
size_t allocations_count = 0;     

// Memory Manager Functions
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
            return;
        }
    }
    fprintf(stderr, "Attempted to free untracked memory at %p\n", ptr);
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
            return new_ptr;
        }
    }
    fprintf(stderr, "Reallocation failed: original pointer not found\n");
    return NULL;
}

void check_memory_leaks() {
    if (allocated_memory > 0) {
        fprintf(stderr, "Memory leak detected: %zu bytes still allocated.\n", allocated_memory);
        for (size_t i = 0; i < allocations_count; ++i) {
            fprintf(stderr, "Leaked memory: %p of size %zu\n", allocations[i].ptr, allocations[i].size);
        }
    } else {
        fprintf(stderr, "No memory leaks detected.\n");
    }
    free(allocations);
    allocations = NULL;
    allocations_count = 0;
}

// HybridArray 
typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} HybridArray;

void hybrid_array_init(HybridArray *array) {
    array->size = 0;
    array->capacity = 0;
    array->data = NULL;
}

void hybrid_array_push_back(HybridArray *array, int value) {
    if (array->capacity == 0) {
        array->capacity = 10;
        array->data = (int *)my_malloc(array->capacity * sizeof(int));
    } else if (array->size == array->capacity) {
        array->capacity *= 2;
        array->data = (int *)my_realloc(array->data, array->capacity * sizeof(int));
    }
    array->data[array->size++] = value;
}

int hybrid_array_get(const HybridArray *array, size_t index) {
    if (index >= array->size) {
        fprintf(stderr, "Index out of bounds: %zu\n", index);
        exit(EXIT_FAILURE);
    }
    return array->data[index];
}

void hybrid_array_destroy(HybridArray *array) {
    if (array->data) {
        my_free(array->data);
    }
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
}

void hybrid_array_print(const HybridArray *array) {
    for (size_t i = 0; i < array->size; ++i) {
        printf("%d ", array->data[i]);
    }
    printf("\n");
}

#endif 
