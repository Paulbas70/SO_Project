#include "buddy_allocator.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    printf("Testing buddy_allocator_malloc and buddy_allocator_free\n");

    uint8_t allocator_buffer[BUDDY_ALLOCATOR_BUFFER_SIZE];

    buddy_allocator_t buddy_allocator;
    buddy_allocator_init(&buddy_allocator, allocator_buffer);

    printf("Buddy allocator initialized with buffer size %d bytes\n", BUDDY_ALLOCATOR_BUFFER_SIZE);

    size_t alloc_sizes[] = {64, 64, 128};
    size_t num_allocs = 3;
    
    // Array to store allocated pointers
    void *allocated_ptrs[num_allocs];

    for (size_t i = 0; i < num_allocs; i++) {
        size_t size = alloc_sizes[i];
        printf("\nAllocating %zu bytes\n", size);
        void *ptr = buddy_allocator_malloc(&buddy_allocator, size);
        if (ptr == NULL) {
            fprintf(stderr, "buddy_allocator_malloc failed for size %zu\n", size);
            continue;
        }
        printf("Allocated %zu bytes at %p\n", size, ptr);
        allocated_ptrs[i] = ptr;

        memset(ptr, 42, size);
        printf("Memory initialized with 42\n");

        uint8_t *data = (uint8_t *)ptr;
        int verification_passed = 1;
        for (size_t j = 0; j < size; j++) {
            if (data[j] != 42) {
                fprintf(stderr, "Memory verification failed at byte %zu\n", j);
                verification_passed = 0;
                break;
            }
        }

        if (verification_passed) {
            printf("Memory verification succeeded for allocation %zu\n", i + 1);
        }
    }

    printf("\nAttempting to allocate a large block to test memory exhaustion\n");
    void *large_ptr = buddy_allocator_malloc(&buddy_allocator, BUDDY_ALLOCATOR_BUFFER_SIZE);
    if (large_ptr == NULL) {
        printf("Correctly handled memory exhaustion: No memory available for large allocation.\n");
    } else {
        fprintf(stderr, "Unexpectedly allocated memory for a block larger than buffer size.\n");
    }

    for (size_t i = 0; i < num_allocs; i++) {
        if (allocated_ptrs[i] != NULL) {
            printf("\nFreeing memory at %p (allocated size: %zu bytes)\n", allocated_ptrs[i], alloc_sizes[i]);
            buddy_allocator_free(&buddy_allocator, allocated_ptrs[i]);
            printf("Freed memory at %p\n", allocated_ptrs[i]);
        }
    }

    printf("\nAllocating after freeing to ensure memory reuse\n");
    for (size_t i = 0; i < num_allocs; i++) {
        size_t size = alloc_sizes[i];
        printf("\nRe-allocating %zu bytes\n", size);
        void *ptr = buddy_allocator_malloc(&buddy_allocator, size);
        if (ptr == NULL) {
            fprintf(stderr, "buddy_allocator_malloc failed for size %zu on re-allocation\n", size);
            continue;
        }
        printf("Re-allocated %zu bytes at %p\n", size, ptr);
        allocated_ptrs[i] = ptr;

        memset(ptr, 7, size);
        printf("Memory initialized with 7\n");

        uint8_t *data = (uint8_t *)ptr;
        int verification_passed = 1;
        for (size_t j = 0; j < size; j++) {
            if (data[j] != 7) {
                fprintf(stderr, "Memory verification failed at byte %zu during re-allocation\n", j);
                verification_passed = 0;
                break;
            }
        }

        if (verification_passed) {
            printf("Memory verification succeeded for re-allocation %zu\n", i + 1);
        }
    }

    for (size_t i = 0; i < num_allocs; i++) {
        if (allocated_ptrs[i] != NULL) {
            printf("\nFinal freeing of memory at %p (allocated size: %zu bytes)\n", allocated_ptrs[i], alloc_sizes[i]);
            buddy_allocator_free(&buddy_allocator, allocated_ptrs[i]);
            printf("Freed memory at %p\n", allocated_ptrs[i]);
        }
    }

    printf("\nBuddy allocator test completed successfully.\n");

    return 0;
}