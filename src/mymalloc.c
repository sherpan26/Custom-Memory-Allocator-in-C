#include "mymalloc.h"
#include <stddef.h> // For size_t
#include <stdio.h>  // For printing error messages

// According to "1.3 Your implementation", this defines the memory used by mymalloc
#define MEMLENGTH 512
static double memory[MEMLENGTH];

// Ensuring 8-byte alignment as per "1.2 Alignment"
#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

// Minimum chunk size to accommodate metadata and alignment requirements
#define MIN_CHUNK_SIZE (sizeof(Metadata) + ALIGNMENT)
#define METADATA_SIZE ALIGN(sizeof(Metadata))

// This struct represents the metadata for each chunk of memory
typedef struct Metadata {
    size_t size; // Chunk size including metadata size
    int is_free; // 1 if the chunk is free, 0 if it's allocated
    struct Metadata *next; // Pointer to the next chunk's metadata
} Metadata;

// Head of the free list
static Metadata *free_list_head = NULL;

// Convert the 'memory' array to a char pointer for byte-wise operations
char *heap_start = (char *)memory;

// Forward declarations
void *mymalloc_internal(size_t size, char *file, int line);
void myfree_internal(void *ptr, char *file, int line);
Metadata *find_free_chunk(Metadata **last, size_t size);
Metadata *extend_heap(Metadata *last, size_t size);
void split_chunk(Metadata *chunk, size_t size);
void coalesce_free_chunks(void);

// The actual 'mymalloc' function called by the macro
void *mymalloc(size_t size, char *file, int line) {
    if (size <= 0) { // Guard against non-positive sizes
        fprintf(stderr, "mymalloc: Invalid size %zu (called from %s:%d)\n", size, file, line);
        return NULL;
    }
    
    // Ensure the allocation size is aligned
    size = ALIGN(size + METADATA_SIZE);

    // Check if the request exceeds the maximum allocation size
    if (size + METADATA_SIZE > MEMLENGTH * sizeof(double)) {
        fprintf(stderr, "mymalloc: Requested size %zu is too large (called from %s:%d)\n", size, file, line);
        return NULL;
    }

    return mymalloc_internal(size, file, line);
}

// Internal function to handle memory allocation
void *mymalloc_internal(size_t size, char *file, int line) {
    Metadata *last = NULL;
    Metadata *free_chunk = find_free_chunk(&last, size);

    if (free_chunk == NULL) {
        free_chunk = extend_heap(last, size);
        if (free_chunk == NULL) {
            fprintf(stderr, "mymalloc: Failed to allocate %zu bytes (called from %s:%d)\n", size, file, line);
            return NULL;
        }
    } else {
        // Optional: Split the chunk if it's significantly larger than requested
        split_chunk(free_chunk, size);
    }

    free_chunk->is_free = 0; // Mark chunk as allocated
    return (void *)((char *)free_chunk + METADATA_SIZE); // Return pointer to payload
}

// The actual 'myfree' function called by the macro
void myfree(void *ptr, char *file, int line) {
    if (!ptr) {
        fprintf(stderr, "myfree: Attempt to free NULL pointer (called from %s:%d)\n", file, line);
        return;
    }

    // Convert the pointer back to Metadata*, adjust for the metadata size
    Metadata *chunk = (Metadata *)((char *)ptr - METADATA_SIZE);
    
    // Error checks for double free or invalid free could go here

    chunk->is_free = 1; // Mark chunk as free

    // Optional: Coalesce adjacent free chunks
    coalesce_free_chunks();
}

// Finds a free chunk of memory that fits the requested size
Metadata *find_free_chunk(Metadata **last, size_t size) {
    Metadata *current = free_list_head;
    while (current && !(current->is_free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    return current;
}

// Extends the heap if no suitable chunk is found
Metadata *extend_heap(Metadata *last, size_t size) {
    Metadata *chunk = (Metadata *)(heap_start + (last ? last->size : 0));
    if ((char *)chunk + size - heap_start > MEMLENGTH * sizeof(double)) {
        return NULL; // Out of memory
    }
    chunk->size = size;
    chunk->is_free = 0;
    chunk->next = NULL;

    if (last) {
        last->next = chunk;
    } else {
        free_list_head = chunk;
    }
    return chunk;
}

// Optional: Splits a larger chunk into two
void split_chunk(Metadata *chunk, size_t size) {
    // Implementation depends on specific strategy and metadata layout
}

// Optional: Coalesces adjacent free chunks into a single chunk
void coalesce_free_chunks() {
    // Implementation depends on specific strategy and metadata layout
}
