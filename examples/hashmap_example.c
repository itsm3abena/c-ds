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
