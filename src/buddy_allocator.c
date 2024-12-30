#include "buddy_allocator.h"

bit_map_t bit_map;
uint8_t bit_map_buffer[BIT_MAP_BUFFER_SIZE];

void buddy_allocator_init(buddy_allocator_t *buddy_allocator, void *buffer) {
    buddy_allocator->buffer = buffer;
    buddy_allocator->depth = BUDDY_ALLOCATOR_MAX_LEVELS;
    buddy_allocator->min_node_size = BUDDY_ALLOCATOR_MIN_NODE_SIZE;
    // TODO: I'm not sure about that
    bit_map_init(&bit_map, bit_map_buffer, BIT_MAP_BUFFER_SIZE);
    buddy_allocator->bit_map = &bit_map;
}

void *buddy_allocator_malloc(size_t sz) {

}

void buddy_allocator_free(void *ptr) {
}