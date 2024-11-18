#ifndef HYBRID_ARRAY_H
#define HYBRID_ARRAY_H

#include <stddef.h>  

typedef struct {
    int *data;     
    size_t size;   
    size_t capacity; 
} HybridArray;

void hybrid_array_init(HybridArray *array);
void hybrid_array_push_back(HybridArray *array, int value);
int hybrid_array_get(const HybridArray *array, size_t index);
void hybrid_array_destroy(HybridArray *array);
void hybrid_array_print(const HybridArray *array);

void hybrid_array_shrink_to_fit(HybridArray *array);
void* my_malloc(size_t size);
void my_free(void* ptr);
void check_memory_leaks();

#endif 
