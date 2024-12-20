/**
 * MIT License

    Copyright (c) 2024 Abenezer L.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct HashmapEntry {
    char *key;
    void *value;
    struct HashmapEntry *next; 
} HashmapEntry;

typedef struct {
    HashmapEntry **buckets; 
    size_t size;            
    size_t count;           
} Hashmap;

static unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; 
    }
    return hash;
}

static Hashmap *hashmap_create(size_t size) {
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

static void hashmap_destroy(Hashmap *map) {
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

static bool hashmap_insert(Hashmap *map, const char *key, void *value) {
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

static void *hashmap_get(Hashmap *map, const char *key) {
    unsigned long hash_value = hash(key) % map->size;
    HashmapEntry *entry = map->buckets[hash_value];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL; 
}

static bool hashmap_remove(Hashmap *map, const char *key) {
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
    return false; 
}

static void hashmap_print(Hashmap *map) {
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

#endif 
