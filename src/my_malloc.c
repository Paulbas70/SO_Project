#include "my_malloc.h"
#include "mmap.h"
#include "buddy_allocator.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

buddy_allocator_t buddy_allocator;
bit_map_t bit_map;
uint8_t buddy_allocator_buffer[BUDDY_ALLOCATOR_BUFFER_SIZE];
uint8_t bit_map_buffer[BIT_MAP_BUFFER_SIZE];

void my_malloc_init() {
    buddy_allocator_init(&buddy_allocator, &buddy_allocator_buffer, &bit_map);
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
        // TODO
        return NULL;
    }
}

void my_free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    if (1) {
        // TODO
    } else {
        mmap_free(ptr);
    }
}