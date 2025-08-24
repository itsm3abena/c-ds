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

#ifndef DS_H
#define DS_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

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


/*  -------   TRIE ------   */

#ifndef TRIE_ALPHABET
#define TRIE_ALPHABET 26 /* 'a'..'z' */


typedef void (*trie_free_fn)(void *p);

typedef struct TrieNode {
    struct TrieNode *child[TRIE_ALPHABET];
    bool terminal;
    void *value;
} TrieNode;

typedef struct Trie {
    TrieNode *root;
    trie_free_fn free_value;
    size_t size;
} Trie;

static inline TrieNode *trie_new_node(void) {
    TrieNode *n = (TrieNode *)calloc(1, sizeof(TrieNode));
    return n;
}

static inline Trie *trie_create(trie_free_fn free_value) {
    Trie *t = (Trie *)malloc(sizeof(Trie));
    if (!t) return NULL;
    t->root = trie_new_node();
    if (!t->root) { free(t); return NULL; }
    t->free_value = free_value;
    t->size = 0;
    return t;
}

static inline void trie_free_node(Trie *t, TrieNode *n) {
    if (!n) return;
    for (int i = 0; i < TRIE_ALPHABET; ++i) trie_free_node(t, n->child[i]);
    if (n->terminal && t->free_value) t->free_value(n->value);
    free(n);
}

static inline void trie_destroy(Trie *t) {
    if (!t) return;
    trie_free_node(t, t->root);
    free(t);
}

static inline int trie_idx(char ch) {
    ch = (char)tolower((unsigned char)ch);
    if (ch < 'a' || ch > 'z') return -1;
    return (int)(ch - 'a');
}

static inline bool trie_insert(Trie *t, const char *word, void *value) {
    if (!t || !word) return false;
    TrieNode *cur = t->root;
    for (const char *p = word; *p; ++p) {
        int id = trie_idx(*p);
        if (id < 0) continue;
        if (!cur->child[id]) cur->child[id] = trie_new_node();
        if (!cur->child[id]) return false;
        cur = cur->child[id];
    }
    if (!cur->terminal) {
        cur->terminal = true;
        cur->value = value;
        t->size++;
        return true;
    } else {
        if (t->free_value) t->free_value(cur->value);
        cur->value = value;
        return false;
    }
}

static inline bool trie_contains(const Trie *t, const char *word) {
    if (!t || !word) return false;
    const TrieNode *cur = t->root;
    for (const char *p = word; *p; ++p) {
        int id = trie_idx(*p);
        if (id < 0) continue;
        cur = cur->child[id];
        if (!cur) return false;
    }
    return cur->terminal;
}

static inline void *trie_get(const Trie *t, const char *word) {
    if (!t || !word) return NULL;
    const TrieNode *cur = t->root;
    for (const char *p = word; *p; ++p) {
        int id = trie_idx(*p);
        if (id < 0) continue;
        cur = cur->child[id];
        if (!cur) return NULL;
    }
    return cur->terminal ? cur->value : NULL;
}

static inline bool trie_starts_with(const Trie *t, const char *prefix) {
    if (!t || !prefix) return false;
    const TrieNode *cur = t->root;
    for (const char *p = prefix; *p; ++p) {
        int id = trie_idx(*p);
        if (id < 0) continue;
        cur = cur->child[id];
        if (!cur) return false;
    }
    return true;
}

static inline bool trie_remove(Trie *t, const char *word) {
    if (!t || !word) return false;

    const char *p = word;
    TrieNode *stack_nodes[256];
    int stack_idx[256];
    int top = 0;

    TrieNode *cur = t->root;
    for (; *p && top < 256; ++p) {
        int id = trie_idx(*p);
        if (id < 0) continue;
        if (!cur->child[id]) return false;
        stack_nodes[top] = cur;
        stack_idx[top] = id;
        top++;
        cur = cur->child[id];
    }
    if (!cur->terminal) return false;

    cur->terminal = false;
    if (t->free_value) t->free_value(cur->value);
    cur->value = NULL;
    t->size--;

    for (int i = top - 1; i >= 0; --i) {
        TrieNode *parent = stack_nodes[i];
        TrieNode *child  = parent->child[stack_idx[i]];
        bool has_child = false;
        for (int k = 0; k < TRIE_ALPHABET; ++k) {
            if (child->child[k]) { has_child = true; break; }
        }
        if (!child->terminal && !has_child) {
            parent->child[stack_idx[i]] = NULL;
            free(child);
        } else break;
    }
    return true;
}

static inline size_t trie_size(const Trie *t) { return t ? t->size : 0; }

#endif




/*---- TREE BST --------*/


typedef struct BSTNode {
    void *key;
    void *value;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

typedef int (*bst_cmp_fn)(const void *a, const void *b);
typedef void (*bst_free_fn)(void *p);

typedef struct BST {
    BSTNode *root;
    bst_cmp_fn cmp;
    bst_free_fn free_key;
    bst_free_fn free_value;
    size_t size;
} BST;

static inline BST *bst_create(bst_cmp_fn cmp, bst_free_fn free_key, bst_free_fn free_value) {
    if (!cmp) return NULL;
    BST *t = (BST *)malloc(sizeof(BST));
    if (!t) return NULL;
    t->root = NULL;
    t->cmp = cmp;
    t->free_key = free_key;
    t->free_value = free_value;
    t->size = 0;
    return t;
}

static inline void bst_free_node(BST *t, BSTNode *n) {
    if (!n) return;
    bst_free_node(t, n->left);
    bst_free_node(t, n->right);
    if (t->free_key)   t->free_key(n->key);
    if (t->free_value) t->free_value(n->value);
    free(n);
}

static inline void bst_destroy(BST *t) {
    if (!t) return;
    bst_free_node(t, t->root);
    free(t);
}

static inline size_t bst_size(const BST *t) { return t ? t->size : 0; }

static inline bool bst_insert(BST *t, void *key, void *value) {
    if (!t) return false;
    BSTNode **cur = &t->root;
    while (*cur) {
        int c = t->cmp(key, (*cur)->key);
        if (c == 0) {
            if (t->free_key)   t->free_key((*cur)->key);
            if (t->free_value) t->free_value((*cur)->value);
            (*cur)->key = key;
            (*cur)->value = value;
            return false;
        }
        cur = (c < 0) ? &(*cur)->left : &(*cur)->right;
    }
    BSTNode *n = (BSTNode *)malloc(sizeof(BSTNode));
    if (!n) return false;
    n->key = key; n->value = value; n->left = n->right = NULL;
    *cur = n;
    t->size++;
    return true;
}

static inline void *bst_get(const BST *t, const void *key) {
    if (!t) return NULL;
    BSTNode *cur = t->root;
    while (cur) {
        int c = t->cmp(key, cur->key);
        if (c == 0) return cur->value;
        cur = (c < 0) ? cur->left : cur->right;
    }
    return NULL;
}

static inline BSTNode *bst_min_with_parent(BSTNode *n, BSTNode **pp) {
    *pp = NULL;
    while (n && n->left) { *pp = n; n = n->left; }
    return n;
}

static inline bool bst_remove(BST *t, const void *key) {
    if (!t) return false;
    BSTNode **link = &t->root;
    BSTNode *parent = NULL;
    while (*link) {
        int c = t->cmp(key, (*link)->key);
        if (c == 0) break;
        parent = *link;
        link = (c < 0) ? &(*link)->left : &(*link)->right;
    }
    BSTNode *target = *link;
    if (!target) return false;

    if (target->left && target->right) {
        BSTNode *ps = NULL;
        BSTNode *succ = bst_min_with_parent(target->right, &ps);

        void *tmpk = target->key; void *tmpv = target->value;
        target->key = succ->key; target->value = succ->value;
        succ->key = tmpk; succ->value = tmpv;

        link = (ps ? &ps->left : &target->right);
        target = *link;
    }

    BSTNode *child = target->left ? target->left : target->right;
    *link = child;

    if (t->free_key)   t->free_key(target->key);
    if (t->free_value) t->free_value(target->value);
    free(target);
    t->size--;
    (void)parent;
    return true;
}

typedef void (*bst_visit_fn)(void *key, void *value, void *user);

static inline void bst_inorder_node(BSTNode *n, bst_visit_fn visit, void *user) {
    if (!n) return;
    bst_inorder_node(n->left, visit, user);
    visit(n->key, n->value, user);
    bst_inorder_node(n->right, visit, user);
}

static inline void bst_inorder(const BST *t, bst_visit_fn visit, void *user) {
    if (!t || !visit) return;
    bst_inorder_node(t->root, visit, user);
}
