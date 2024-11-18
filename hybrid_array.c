#include <stdio.h>
#include <stdlib.h>
#include "hybrid_array.h" 


void hybrid_array_init(HybridArray *array) {
    array->size = 0;
    array->capacity = 4; 
    array->data = (int*)malloc(array->capacity * sizeof(int));
    if (!array->data) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

void hybrid_array_push_back(HybridArray *array, int value) {
    if (array->size >= array->capacity) {
        size_t new_capacity = (array->capacity == 0) ? 1 : array->capacity * 2;

        int* new_data = my_malloc(sizeof(int) * new_capacity);

        for (size_t i = 0; i < array->size; ++i) {
            new_data[i] = array->data[i];
        }

        my_free(array->data);
        
        array->data = new_data;
        array->capacity = new_capacity;
    }

    array->data[array->size] = value;
    array->size++;
}


void hybrid_array_shrink_to_fit(HybridArray *array) {
    if (array->size < array->capacity) {
        int* new_data = my_malloc(sizeof(int) * array->size);

        for (size_t i = 0; i < array->size; ++i) {
            new_data[i] = array->data[i];
        }

        my_free(array->data);

        array->data = new_data;
        array->capacity = array->size;
    }
}


void hybrid_array_reserve(HybridArray *array, size_t new_capacity) {
    if (new_capacity > array->capacity) {

        int* new_data = my_malloc(sizeof(int) * new_capacity);

        for (size_t i = 0; i < array->size; ++i) {
            new_data[i] = array->data[i];
        }

        my_free(array->data);

        array->data = new_data;
        array->capacity = new_capacity;
    }
}



int hybrid_array_get(const HybridArray *array, size_t index) {
    if (index >= array->size) {
        fprintf(stderr, "Index out of bounds: %zu\n", index);
        exit(EXIT_FAILURE);
    }
    return array->data[index];
}

void hybrid_array_destroy(HybridArray *array) {
    if (array->data != NULL) {
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
