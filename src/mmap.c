#include "mmap.h"

#include <sys/mman.h>
#include <stdio.h>

void *mmap_malloc(size_t sz) {
    void *ptr = mmap(NULL, sizeof(size_t) + sz, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return NULL;
    }

    // Store the size at the beginning of the mapped region
    *((size_t *)ptr) = sz;

    // Return a pointer to the memory region after the size
    return (void *)((char *)ptr + sizeof(size_t));
}

void mmap_free(void *ptr) {
    // Retrieve the original mapped address by stepping back sizeof(size_t) bytes
    void *mapped = (void *)((char *)ptr - sizeof(size_t));

    // Read the size of the mapped memory from the metadata
    size_t size = *((size_t *)mapped);

    int ret = munmap(mapped, size);

    if (ret == -1) {
        perror("munmap");
    }
}