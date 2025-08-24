#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

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

#endif
