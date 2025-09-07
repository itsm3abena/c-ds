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
