#include "mymalloc.h"
#include <stdio.h>
#include <stdlib.h> // For random number generation

#define LARGE_ALLOCATION_SIZE 256 // Size of large allocations to stress the allocator
#define SMALL_ALLOCATION_SIZE 16  // Size of small allocations to test granularity
#define NUM_ALLOCATIONS 10        // Number of allocations to perform for each size

int main() {
    printf("Running TestD...\n");

    // Step 1: Allocate several large blocks to consume a significant portion of memory
    void *largeBlocks[NUM_ALLOCATIONS];
    for (int i = 0; i < NUM_ALLOCATIONS; i++) {
        largeBlocks[i] = malloc(LARGE_ALLOCATION_SIZE);
        if (largeBlocks[i] == NULL) {
            printf("Failed to allocate large block %d\n", i);
            return 1; // Exit if we cannot allocate memory
        }
    }

    // Step 2: Free every other large block to create fragmented free spaces
    for (int i = 0; i < NUM_ALLOCATIONS; i += 2) {
        free(largeBlocks[i]);
    }

    // Step 3: Attempt to allocate numerous small blocks, testing the allocator's ability to utilize fragmented space
    void *smallBlocks[NUM_ALLOCATIONS * 2]; // Allocate twice the number of small blocks
    for (int i = 0; i < NUM_ALLOCATIONS * 2; i++) {
        smallBlocks[i] = malloc(SMALL_ALLOCATION_SIZE);
        if (smallBlocks[i] == NULL) {
            printf("Failed to allocate small block %d\n", i);
            // No exit here to see how many small allocations can succeed
        }
    }

    // Step 4: Cleanup - Free remaining large blocks and all small blocks
    for (int i = 1; i < NUM_ALLOCATIONS; i += 2) { // Free the unfreed large blocks
        free(largeBlocks[i]);
    }
    for (int i = 0; i < NUM_ALLOCATIONS * 2; i++) { // Free all small blocks
        if (smallBlocks[i] != NULL) {
            free(smallBlocks[i]);
        }
    }

    printf("TestD completed successfully.\n");

    return 0;
}
