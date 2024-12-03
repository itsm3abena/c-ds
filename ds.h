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
    return NULL;
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
    return false;
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

// =======================================
// Linked List Implementation
// =======================================

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtHead(Node** head, int data) {
    Node* newNode = createNode(data);
    if (!newNode) return;
    newNode->next = *head;
    *head = newNode;
}

void insertAtTail(Node** head, int data) {
    Node* newNode = createNode(data);
    if (!newNode) return;
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void deleteNode(Node** head, int data) {
    if (*head == NULL) return;

    Node* temp = *head;
    if (temp->data == data) {
        *head = temp->next;
        free(temp);
        return;
    }

    Node* prev = NULL;
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

Node* search(Node* head, int data) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == data) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

#endif 
