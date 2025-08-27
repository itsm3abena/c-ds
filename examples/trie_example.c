#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ds.h"

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
