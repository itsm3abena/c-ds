#include <stdio.h>
#include <stdlib.h>
#include "hybrid_array.h"

void hybrid_array_init(HybridArray *array) {
    array->size = 0;
    array->capacity = 0;  
    array->data = NULL;   
}

void hybrid_array_push_back(HybridArray *array, int value) {
    if (array->data == NULL) {
        array->capacity = 10; 
        array->data = (int *)malloc(array->capacity * sizeof(int));
        
        if (array->data == NULL) {
            fprintf(stderr, "Memory allocation failed! Capacity: %zu\n", array->capacity);
            exit(EXIT_FAILURE); 
        }
    }

    if (array->size == array->capacity) {
        array->capacity *= 2;
        int *new_data = (int *)realloc(array->data, array->capacity * sizeof(int));

        if (new_data == NULL) {
            fprintf(stderr, "Memory reallocation failed! New capacity: %zu\n", array->capacity);
            free(array->data); 
            exit(EXIT_FAILURE); 
        }

        array->data = new_data;
    }

    array->data[array->size++] = value;
}

void hybrid_array_shrink_to_fit(HybridArray *array) {
    if (array->size < array->capacity) {
        int* new_data = (int *)malloc(array->size * sizeof(int));

        if (new_data == NULL) {
            fprintf(stderr, "Memory allocation failed! Shrinking to fit.\n");
            exit(EXIT_FAILURE); 
        }

        for (size_t i = 0; i < array->size; ++i) {
            new_data[i] = array->data[i];
        }

        free(array->data);

        array->data = new_data;
        array->capacity = array->size;
    }
}

void hybrid_array_reserve(HybridArray *array, size_t new_capacity) {
    if (new_capacity > array->capacity) {
        int* new_data = (int *)malloc(sizeof(int) * new_capacity);

        if (new_data == NULL) {
            fprintf(stderr, "Memory allocation failed! Requested capacity: %zu\n", new_capacity);
            exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < array->size; ++i) {
            new_data[i] = array->data[i];
        }

        free(array->data);

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
        free(array->data);
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

