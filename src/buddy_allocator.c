#include "buddy_allocator.h"

void buddy_allocator_init(buddy_allocator_t *buddy_allocator, void *buffer, bit_map_t *bit_map) {
    buddy_allocator->bit_map = bit_map;
    buddy_allocator->buffer = buffer;
    buddy_allocator->depth = BUDDY_ALLOCATOR_MAX_LEVELS;
    buddy_allocator->min_node_size = BUDDY_ALLOCATOR_MIN_NODE_SIZE;
}

void *buddy_allocator_malloc(size_t sz) {

}

void buddy_allocator_free(void *ptr) {
}