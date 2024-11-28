#include "ds.h"

int main() {
    Hashmap *map = hashmap_create(10);
    if (!map) {
        fprintf(stderr, "Failed to create hashmap\n");
        return 1;
    }

    hashmap_insert(map, "name", "Abena");
    hashmap_insert(map, "age", "24");
    hashmap_insert(map, "city", "Addis Ababa");

    printf("Name: %s\n", (char *)hashmap_get(map, "name"));
    printf("Age: %s\n", (char *)hashmap_get(map, "age"));
    printf("City: %s\n", (char *)hashmap_get(map, "city"));

    hashmap_remove(map, "age");
    printf("Age after removal: %s\n", (char *)hashmap_get(map, "age"));

    hashmap_print(map);

    hashmap_destroy(map);
    return 0;
}
