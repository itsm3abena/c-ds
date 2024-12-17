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

/**
 * @brief Initializes a HybridArray structure.
 * 
 * @param array Pointer to the HybridArray to initialize.
 */
void hybrid_array_init(HybridArray *array) {
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
}

/**
 * @brief Adds a value to the end of the HybridArray.
 * 
 * @param array Pointer to the HybridArray.
 * @param value The integer value to add to the array.
 */
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

/**
 * @brief Retrieves the value at a specific index in the HybridArray.
 * 
 * @param array Pointer to the HybridArray.
 * @param index The index of the value to retrieve.
 * @return The integer value at the specified index.
 * @note Exits the program if the index is out of bounds.
 */
int hybrid_array_get(const HybridArray *array, size_t index) {
    if (index >= array->size) {
        fprintf(stderr, "Index out of bounds: %zu\n", index);
        exit(EXIT_FAILURE);
    }
    return array->data[index];
}

/**
 * @brief Frees the memory used by the HybridArray.
 * 
 * @param array Pointer to the HybridArray to destroy.
 */
void hybrid_array_destroy(HybridArray *array) {
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
}

/**
 * @brief Prints the contents of the HybridArray.
 * 
 * @param array Pointer to the HybridArray.
 */
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

/**
 * @brief Creates a new hashmap.
 * 
 * @param size The number of buckets in the hashmap.
 * @return Pointer to the newly created Hashmap, or NULL if memory allocation fails.
 */
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

/**
 * @brief Frees the memory used by the hashmap.
 * 
 * @param map Pointer to the Hashmap to destroy.
 */
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

/**
 * @brief Inserts a key-value pair into the hashmap.
 * 
 * @param map Pointer to the Hashmap.
 * @param key The string key for the entry.
 * @param value Pointer to the value associated with the key.
 * @return True if insertion was successful, false otherwise.
 */
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

/**
 * @brief Retrieves a value associated with a key in the hashmap.
 * 
 * @param map Pointer to the Hashmap.
 * @param key The string key to look up.
 * @return Pointer to the value associated with the key, or NULL if the key is not found.
 */
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

/**
 * @brief Removes a key-value pair from the hashmap.
 * 
 * @param map Pointer to the Hashmap.
 * @param key The string key to remove.
 * @return True if the key was successfully removed, false if the key was not found.
 */
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

/**
 * @brief Prints the contents of the hashmap.
 * 
 * @param map Pointer to the Hashmap.
 */
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

/**
 * @brief Creates a new node with the given data.
 * 
 * @param data The integer data for the new node.
 * @return Pointer to the newly created node, or NULL if memory allocation fails.
 */
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

/**
 * @brief Inserts a new node with the given data at the head of the list.
 * 
 * @param head Pointer to the pointer to the head of the list.
 * @param data The integer data to insert.
 */
void insertAtHead(Node** head, int data) {
    Node* newNode = createNode(data);
    if (!newNode) return;
    newNode->next = *head;
    *head = newNode;
}

/**
 * @brief Inserts a new node with the given data at the tail of the list.
 * 
 * @param head Pointer to the pointer to the head of the list.
 * @param data The integer data to insert.
 */
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

/**
 * @brief Deletes the first node with the given data value.
 * 
 * @param head Pointer to the pointer to the head of the list.
 * @param data The integer value to delete from the list.
 */
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

/**
 * @brief Searches for a node with the specified data.
 * 
 * @param head Pointer to the head of the list.
 * @param data The integer value to search for.
 * @return Pointer to the node containing the data, or NULL if not found.
 */
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

/**
 * @brief Prints the contents of the linked list.
 * 
 * @param head Pointer to the head of the list.
 */
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

/**
 * @brief Frees the memory allocated for the linked list.
 * 
 * @param head Pointer to the head of the list.
 */
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

#endif 
