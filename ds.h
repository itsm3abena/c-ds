#ifndef DS_H
#define DS_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

// =======================================
// HybridArray Implementation
// =======================================
typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} HybridArray;

void hybrid_array_init(HybridArray *array) {
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
}

void hybrid_array_push_back(HybridArray *array, int value) {
    if (array->capacity == 0) {
        array->capacity = 10;
        array->data = malloc(array->capacity * sizeof(int));
    } else if (array->size == array->capacity) {
        array->capacity *= 2;
        array->data = realloc(array->data, array->capacity * sizeof(int));
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
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
}

void hybrid_array_print(const HybridArray *array) {
    for (size_t i = 0; i < array->size; i++) {
        printf("%d ", array->data[i]);
    }
    printf("\n");
}

// =======================================
// Hashmap Implementation
// =======================================
typedef struct HashmapEntry {
    char *key;
    void *value;
    struct HashmapEntry *next; // For collision handling (chaining)
} HashmapEntry;

typedef struct {
    HashmapEntry **buckets; // Array of pointers to entries
    size_t size;            // Number of buckets
    size_t count;           // Number of elements in the hashmap
} Hashmap;

static unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

Hashmap *hashmap_create(size_t size) {
    Hashmap *map = malloc(sizeof(Hashmap));
    if (!map) return NULL;
    map->buckets = calloc(size, sizeof(HashmapEntry *));
    if (!map->buckets) {
        free(map);
        return NULL;
    }
    map->size = size;
    map->count = 0;
    return map;
}

void hashmap_destroy(Hashmap *map) {
    for (size_t i = 0; i < map->size; i++) {
        HashmapEntry *entry = map->buckets[i];
        while (entry) {
            HashmapEntry *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }
    free(map->buckets);
    free(map);
}

bool hashmap_insert(Hashmap *map, const char *key, void *value) {
    unsigned long hash_value = hash(key) % map->size;
    HashmapEntry *new_entry = malloc(sizeof(HashmapEntry));
    if (!new_entry) return false;

    new_entry->key = strdup(key);
    if (!new_entry->key) {
        free(new_entry);
        return false;
    }
    new_entry->value = value;
    new_entry->next = map->buckets[hash_value];
    map->buckets[hash_value] = new_entry;
    map->count++;
    return true;
}

void *hashmap_get(Hashmap *map, const char *key) {
    unsigned long hash_value = hash(key) % map->size;
    HashmapEntry *entry = map->buckets[hash_value];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL; // Key not found
}

bool hashmap_remove(Hashmap *map, const char *key) {
    unsigned long hash_value = hash(key) % map->size;
    HashmapEntry *entry = map->buckets[hash_value];
    HashmapEntry *prev = NULL;

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                map->buckets[hash_value] = entry->next;
            }
            free(entry->key);
            free(entry);
            map->count--;
            return true;
        }
        prev = entry;
        entry = entry->next;
    }
    return false; // Key not found
}

void hashmap_print(Hashmap *map) {
    printf("Hashmap contents:\n");
    for (size_t i = 0; i < map->size; i++) {
        HashmapEntry *entry = map->buckets[i];
        if (entry) {
            printf("Bucket %zu: ", i);
            while (entry) {
                printf("(%s -> %p) ", entry->key, entry->value);
                entry = entry->next;
            }
            printf("\n");
        }
    }
}

#endif // DATA_STRUCTURES_H
