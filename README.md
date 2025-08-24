# Data Structures in C - Single Header Library (ds.h)

Welcome to the Data Structures in C project! This repository provides a single-header library, ds.h, that includes implementations for various data structures. Just include this header in your project, and you're ready to use powerful and efficient data structures with ease.
Features

The library includes the following data structures:

## Hashmaps
A key-value store using chaining to handle hash collisions.
Supported Operations:

- insert – Add key-value pairs to the map
- find – Retrieve the value for a given key
- remove – Delete a key-value pair
- print – Display the hashmap contents
- destroy – Clean up memory used by the hashmap

Example: 
```c
#include "ds.h"

int main() {
    Hashmap *map = hashmap_create(10);
    if (!map) {
        fprintf(stderr, "Failed to create hashmap\n");
        return 1;
    }

    hashmap_insert(map, "name", "Abena");
    hashmap_insert(map, "age", "24");
    hashmap_insert(map, "city", "Addis Ababa");

    printf("Name: %s\n", (char *)hashmap_get(map, "name"));
    printf("Age: %s\n", (char *)hashmap_get(map, "age"));
    printf("City: %s\n", (char *)hashmap_get(map, "city"));

    hashmap_remove(map, "age");
    printf("Age after removal: %s\n", (char *)hashmap_get(map, "age"));

    hashmap_print(map);

    hashmap_destroy(map);
    return 0;
}

```

## Hybrid Arrays
An automatically resizable array that grows dynamically as elements are added.
Supported Operations:

- push_back – Append an element to the array
- get – Access an element at a given index
- print – Display the array contents
- destroy – Free memory allocated to the array

Example: Hybrid Array Usage
```c
#include "ds.h"
#include <stdio.h>

int main() {
    printf("=== Hybrid Array Example ===\n");

    // Initialize a HybridArray
    HybridArray array;
    hybrid_array_init(&array);

    // Add elements to the array
    hybrid_array_push_back(&array, 10);
    hybrid_array_push_back(&array, 20);
    hybrid_array_push_back(&array, 30);

    // Print the array's contents
    printf("Array contents: ");
    hybrid_array_print(&array);

    // Access elements by index
    printf("Element at index 0: %d\n", hybrid_array_get(&array, 0));
    printf("Element at index 1: %d\n", hybrid_array_get(&array, 1));
    printf("Element at index 2: %d\n", hybrid_array_get(&array, 2));

    // Clean up memory
    hybrid_array_destroy(&array);

    return 0;
}

```

## Linked Lists
A singly linked list implementation with convenient operations.
Supported Operations:

- insertAtHead – Insert an element at the beginning
- insertAtTail – Insert an element at the end
- deleteNode – Delete a node with a specific value
- search – Find a node by its value
- printList – Display the contents of the list
- freeList – Release memory used by the list

Example: Linked List Usage
```c
#include "linked_list.h"

int main() {
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

```

## Binary Search Tree (BST)

A simple integer BST with fast insert/search/delete.
Supported Operations:

- bst_insert – Insert a value

- bst_search – Check if a value exists

- bst_delete – Delete a value (returns the new root)

- bst_inorder_print – Display the tree in sorted order

- bst_free – Release memory used by the tree

Example: BST Usage
```c
#include "tree.h"
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
```

## Trie

A prefix tree for lowercase a–z words (other characters are ignored).
Supported Operations:

- trie_insert – Insert a word

- trie_search – Check if a word exists

- trie_starts_with – Check if any word has the given prefix

- trie_delete – Remove a word and prune unused nodes

- trie_free – Release memory used by the trie

Example: Trie Usage
```c
#include "trie.h"

int main(void) {
    Trie *tr = trie_create(free);

    trie_insert(tr, "hello", strdup("world"));
    trie_insert(tr, "help",  strdup("me"));
    trie_insert(tr, "helium",strdup("gas"));

    printf("contains 'help'? %s\n", trie_contains(tr, "help") ? "yes" : "no");
    printf("starts_with 'he'? %s\n", trie_starts_with(tr, "he") ? "yes" : "no");
    printf("value at 'hello': %s\n", (char*)trie_get(tr, "hello"));

    trie_remove(tr, "help");
    printf("contains 'help' after remove? %s\n", trie_contains(tr, "help") ? "yes" : "no");
    printf("trie size: %zu\n", trie_size(tr));

    trie_destroy(tr);
    return 0;
}
```

## How to Use
1. Include the Header
Download the ds.h file and place it in your project directory. Include it in your source file as follows:
```c
#include "ds.h"
```

2. Compile Your Code
Use a C compiler such as gcc to compile your program. For example:
```shell
gcc -o my_program main.c
```

3. Run the Program
Execute the compiled output:
```shell
./my_program   # On Linux or macOS
my_program.exe # On Windows
```

## Benefits
Single Header Library: Simple integration – no separate source files needed.
Efficient Implementations: Optimized for performance and memory usage.
Reusable: Designed for use in various applications without modifications.

## License
This project is released under the MIT License. See the [LICENSE](https://github.com/itsm3abena/c-ds/blob/main/LICENSE) file for more details.
Contributing

We welcome contributions! To improve the library, fix bugs, or add new features:

1. Fork the repository.
2. Create a new branch.
3. Commit your changes.
4. Submit a pull request.

## Contact

For questions, suggestions, or feedback, feel free to reach out:

GitHub Issues: Open an [issue](https://github.com/itsm3abena/c-ds/issues) on this repository.
