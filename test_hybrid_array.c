#include "ds.h"
#include <stdio.h>

int main() {
    HybridArray array;
    hybrid_array_init(&array);

    hybrid_array_push_back(&array, 10);
    hybrid_array_push_back(&array, 20);
    hybrid_array_push_back(&array, 30);

    hybrid_array_print(&array);

    printf("Element at index 0: %d\n", hybrid_array_get(&array, 0));
    printf("Element at index 1: %d\n", hybrid_array_get(&array, 1));

    hybrid_array_destroy(&array);

    printf("\n=== Hashmap Example ===\n");

    Hashmap *map = hashmap_create(10);
    
    int value1 = 42;
    double value2 = 3.14;
    char *value3 = "Hello";

    hashmap_insert(map, "key1", &value1);
    hashmap_insert(map, "key2", &value2);
    hashmap_insert(map, "key3", value3);

    hashmap_print(map);

    printf("Value for 'key1': %d\n", *(int *)hashmap_get(map, "key1"));
    printf("Value for 'key2': %.2f\n", *(double *)hashmap_get(map, "key2"));
    printf("Value for 'key3': %s\n", (char *)hashmap_get(map, "key3"));

    hashmap_remove(map, "key2");
    printf("\nAfter removing 'key2':\n");
    hashmap_print(map);

    hashmap_destroy(map);

    return 0;
}
