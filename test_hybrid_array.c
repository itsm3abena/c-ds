#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hybrid_array.h"
#include "memory_manager.h"


void run_basic_tests() {
    HybridArray array;

    hybrid_array_init(&array);

    printf("Adding elements to the array...\n");
    for (int i = 1; i <= 100; ++i) {
        hybrid_array_push_back(&array, i);
    }

    printf("Array contents: ");
    hybrid_array_print(&array);

    printf("\nTesting random element access...\n");
    int num_tests = 10;
    for (int i = 0; i < num_tests; ++i) {
        int random_index = rand() % array.size;
        int element = hybrid_array_get(&array, random_index);

        printf("Element at random index %d: %d (Expected: %d)\n", random_index, element, random_index + 1);
    }

    int first_element = hybrid_array_get(&array, 0);
    int last_element = hybrid_array_get(&array, array.size - 1);
    if (first_element != -1) {
        printf("First element: %d (Expected: 0)\n", first_element);
    }
    if (last_element != -1) {
        printf("Last element: %d (Expected: 99)\n", last_element);
    }


    int invalid_index = 20;
    int result = hybrid_array_get(&array, invalid_index);
    if (result == -1) {
        printf("Out-of-bounds access for index %d.\n", invalid_index);
    } else {
        printf("Element at index %d: %d\n", invalid_index, result);
    }

    hybrid_array_destroy(&array);
    
    check_memory_leaks();

}

int main() {
    printf("Running basic tests...\n");
    run_basic_tests();
    
    return 0;
}
