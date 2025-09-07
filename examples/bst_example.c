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
