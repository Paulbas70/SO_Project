#include "mmap.h"
#include <stdio.h>
#include <string.h>

int main() {
    printf("Testing mmap_malloc and mmap_free\n");
    
    size_t size = 4096;
    
    // Allocate memory using mmap_malloc
    void *ptr = mmap_malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "mmap_malloc failed");
        return 1;
    }
    
    printf("Allocated %zu bytes at %p\n", size, ptr);

    // Taking the size written by mmap_malloc, before the ptr
    size_t *ptr_to_size = (size_t *)((char *)ptr - sizeof(size_t));
    size_t size_written = *ptr_to_size;
    if (size_written != size) {
        fprintf(stderr, "mmap_malloc failed to write the size allocated");
        return 1;
    }
    printf("Size written correctly\n");

    // Initialize the allocated memory with 42
    memset(ptr, 42, size);
    printf("Memory initialized with 42\n");
    
    // Verify the memory content
    unsigned char *data = (unsigned char *)ptr;
    int verification_passed = 1;
    for (size_t i = 0; i < size; i++) {
        if (data[i] != 42) {
            fprintf(stderr, "Memory verification failed at byte %zu\n", i);
            verification_passed = 0;
            break;
        }
    }
    
    if (verification_passed) {
        printf("Memory verification succeeded\n");
    }
    
    // Free the allocated memory using mmap_free
    mmap_free(ptr);
    printf("Freed memory at %p\n", ptr);
    
    return verification_passed ? 0 : 1;
}