#include "my_malloc.h"
#include "mmap.h"
#include "buddy_allocator.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

buddy_allocator_t buddy_allocator;
uint8_t buddy_allocator_buffer[BUDDY_ALLOCATOR_BUFFER_SIZE];

void my_malloc_init() {
    buddy_allocator_init(&buddy_allocator, &buddy_allocator_buffer);
}

void *my_malloc(size_t sz) {
    if (sz == 0) {
        return NULL;
    }

    long page_size = sysconf(_SC_PAGESIZE);
    if (page_size == -1) {
        fprintf(stderr, "sysconf failed to get page size");
        return NULL;
    }

    if ((size_t)page_size / 4 < sz) {
        return mmap_malloc(sz);
    } else {
        return buddy_allocator_malloc(&buddy_allocator, sz);
    }
}

void my_free(void *ptr) {
    if (ptr == NULL) {
        return;
    }
    
    // Cast to uint8_t * to compare pointers and avoid warnings
    uint8_t *ptr_byte = (uint8_t *)ptr;
    if (buddy_allocator_buffer <= ptr_byte && ptr_byte < buddy_allocator_buffer + BUDDY_ALLOCATOR_BUFFER_SIZE) {
        buddy_allocator_free(&buddy_allocator, ptr);
    } else {
        mmap_free(ptr);
    }
}