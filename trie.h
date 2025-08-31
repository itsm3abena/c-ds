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

#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>

#ifndef TRIE_ALPHABET
#define TRIE_ALPHABET 26 /* 'a'..'z' */
#endif

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
