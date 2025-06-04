#include "mymalloc.h"
#include <stdio.h>
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time()

#define MAX_ALLOCATIONS 120 // Maximum number of allocations to perform

int main() {
    printf("Running TestC...\n");
    srand(time(NULL)); // Seed the random number generator

    void *allocatedPointers[MAX_ALLOCATIONS];
    int allocations = 0; // Keep track of the number of successful allocations

    // Initialize all pointers to NULL
    for (int i = 0; i < MAX_ALLOCATIONS; i++) {
        allocatedPointers[i] = NULL;
    }

    while (allocations < MAX_ALLOCATIONS) {
        // Randomly choose between allocation and deallocation
        if (rand() % 2 == 0 || allocations == 0) { // Allocate if no allocations have been made yet
            // Attempt to allocate memory
            void *ptr = malloc(1); // Allocate 1 byte
            if (ptr != NULL) {
                // Find a NULL spot in the array to store this pointer
                for (int i = 0; i < MAX_ALLOCATIONS; i++) {
                    if (allocatedPointers[i] == NULL) {
                        allocatedPointers[i] = ptr;
                        allocations++;
                        break;
                    }
                }
            }
        } else {
            // Attempt to deallocate a random block of memory, if any
            int index = rand() % MAX_ALLOCATIONS;
            if (allocatedPointers[index] != NULL) {
                free(allocatedPointers[index]);
                allocatedPointers[index] = NULL;
                allocations--; // Adjust the allocation count
            }
        }
    }

    // Clean up: Ensure all allocated memory is freed
    for (int i = 0; i < MAX_ALLOCATIONS; i++) {
        if (allocatedPointers[i] != NULL) {
            free(allocatedPointers[i]);
        }
    }

    printf("TestC completed successfully.\n");

    return 0;
}
