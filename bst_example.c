#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ds.h"

static int cmp_str(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

static void visit_print(void *k, void *v, void *u) {
    (void)u;
    printf("%s => %s\n", (char*)k, (char*)v);
}

int main(void) {
    BST *t = bst_create(cmp_str, free, free);
    if (!t) return 1;

    bst_insert(t, strdup("name"), strdup("Abena"));
    bst_insert(t, strdup("city"), strdup("Addis Ababa"));
    bst_insert(t, strdup("role"), strdup("C dev"));
    bst_insert(t, strdup("city"), strdup("Accra"));

    printf("role: %s\n", (char*)bst_get(t, "role"));
    printf("size before delete: %zu\n", bst_size(t));
    bst_remove(t, "name");
    printf("size after delete: %zu\n\n", bst_size(t));

    puts("In-order traversal:");
    bst_inorder(t, visit_print, NULL);

    bst_destroy(t);
    return 0;
}
