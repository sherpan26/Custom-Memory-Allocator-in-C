#include "mymalloc.h"
#include <stdio.h>

#define TOTAL_ALLOCATIONS 120 // Total number of allocations to perform

int main() {
    printf("Running TestB...\n");

    // Array to hold pointers to allocated memory
    void *allocatedPointers[TOTAL_ALLOCATIONS];
    
    // Attempt to allocate memory for each pointer
    for (int i = 0; i < TOTAL_ALLOCATIONS; i++) {
        allocatedPointers[i] = malloc(1); // Allocate 1 byte of memory
        if (allocatedPointers[i] == NULL) {
            printf("malloc failed at allocation %d\n", i);
            // If allocation fails, exit early (might want to free already allocated memory before exiting)
            return 1;
        }
    }

    // Verify that memory was allocated (optional step depending on your test's goals)
    for (int i = 0; i < TOTAL_ALLOCATIONS; i++) {
        // You might want to write some data to the allocated memory here to test further.
        // For simplicity, this step is omitted.
    }

    // Free all allocated memory
    for (int i = 0; i < TOTAL_ALLOCATIONS; i++) {
        free(allocatedPointers[i]);
    }

    printf("TestB completed successfully.\n");

    return 0;
}
