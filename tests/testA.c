#include "mymalloc.h"
#include <stdio.h>

int main() {
    printf("Running testA...\n");

    // Example of allocating and immediately freeing a small chunk of memory
    char *ptr = malloc(1);
    if (ptr == NULL) {
        printf("malloc failed to allocate memory\n");
    } else {
        printf("Memory allocated and now freeing...\n");
        free(ptr);
    }

    // Further tests can be added here

    return 0;
}
