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

#include "ds.h"
#include <stdio.h>

int main() {
    printf("\n=== Dynamic Example ===\n");

    HybridArray array;
    hybrid_array_init(&array);

    hybrid_array_push_back(&array, 10);
    hybrid_array_push_back(&array, 20);
    hybrid_array_push_back(&array, 30);

    hybrid_array_print(&array);

    printf("Element at index 0: %d\n", hybrid_array_get(&array, 0));
    printf("Element at index 1: %d\n", hybrid_array_get(&array, 1));

    hybrid_array_destroy(&array);

    printf("\n=== Hashmap Example ===\n");

    Hashmap *map = hashmap_create(10);
    
    int value1 = 42;
    double value2 = 3.14;
    char *value3 = "Hello";

    hashmap_insert(map, "key1", &value1);
    hashmap_insert(map, "key2", &value2);
    hashmap_insert(map, "key3", value3);

    hashmap_print(map);

    printf("Value for 'key1': %d\n", *(int *)hashmap_get(map, "key1"));
    printf("Value for 'key2': %.2f\n", *(double *)hashmap_get(map, "key2"));
    printf("Value for 'key3': %s\n", (char *)hashmap_get(map, "key3"));

    hashmap_remove(map, "key2");
    printf("\nAfter removing 'key2':\n");
    hashmap_print(map);

    hashmap_destroy(map);

    printf("\n=== Linked List Example ===\n");

    Node* head = NULL;

    insertAtHead(&head, 10);
    insertAtHead(&head, 20);
    insertAtTail(&head, 30);

    printList(head);

    deleteNode(&head, 20);
    printList(head);

    freeList(head);

    return 0;
}
