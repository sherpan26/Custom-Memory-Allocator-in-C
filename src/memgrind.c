#include "mymalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> // For measuring execution time
#include <unistd.h>

// Function prototypes for the different tests to be performed
void testA(); // malloc() and immediately free() a 1-byte object, 120 times
void testB(); // Use malloc() to get 120 1-byte objects, then free() them all
void testC(); // Randomly allocate or free 1-byte objects until 120 allocations are done
void testD(); // User-defined stress test 1
void testE(); // User-defined stress test 2
long getTime(); // Helper function to get current time in microseconds

int main() {
    srand(time(NULL)); // Seed the random number generator

    // Run each test 50 times and measure the time taken for each
    long totalTimeA = 0, totalTimeB = 0, totalTimeC = 0, totalTimeD = 0, totalTimeE = 0;
    for (int i = 0; i < 50; i++) {
        long startTime, endTime;

        startTime = getTime();
        testA();
        endTime = getTime();
        totalTimeA += (endTime - startTime);

        startTime = getTime();
        testB();
        endTime = getTime();
        totalTimeB += (endTime - startTime);

        startTime = getTime();
        testC();
        endTime = getTime();
        totalTimeC += (endTime - startTime);

        startTime = getTime();
        testD();
        endTime = getTime();
        totalTimeD += (endTime - startTime);

        startTime = getTime();
        testE();
        endTime = getTime();
        totalTimeE += (endTime - startTime);
    }

    // Calculate and print the average time for each test
    printf("Average time for test A: %ld microseconds\n", totalTimeA / 50);
    printf("Average time for test B: %ld microseconds\n", totalTimeB / 50);
    printf("Average time for test C: %ld microseconds\n", totalTimeC / 50);
    printf("Average time for test D: %ld microseconds\n", totalTimeD / 50);
    printf("Average time for test E: %ld microseconds\n", totalTimeE / 50);

    return 0;
}

void testA() {
    for (int i = 0; i < 120; i++) {
        char *ptr = malloc(1);
        free(ptr);
    }
}

void testB() {
    char *ptrs[120];
    for (int i = 0; i < 120; i++) {
        ptrs[i] = malloc(1);
    }
    for (int i = 0; i < 120; i++) {
        free(ptrs[i]);
    }
}

void testC() {
    // Implementation of testC based on instructions
    // This involves random allocation and deallocation until 120 allocations are done.
    // Implement as per instructions, ensuring to deallocate any remaining objects at the end.
}

void testD() {
    // User-defined stress test 1
    // Design a test that pushes the limits of your memory allocator in unique ways.
    // For example, alternating between allocations of varying sizes and strategic frees.
}

void testE() {
    // User-defined stress test 2
    // Implement another challenging scenario for your allocator, possibly focusing on edge cases
    // or specific conditions that are likely to occur in real-world applications.
}

long getTime() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000000 + time.tv_usec;
}
