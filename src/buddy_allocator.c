#include "buddy_allocator.h"

#include <stdio.h>
#include <stdlib.h>

bit_map_t bit_map;
uint8_t bit_map_buffer[BIT_MAP_BUFFER_SIZE];

size_t get_left_child(size_t idx) {
    return 2 * idx + 1;
}

size_t get_right_child(size_t idx) {
    return 2 * idx + 2;
}

size_t get_parent(size_t idx) {
    return (idx - 1) / 2;
}

uint8_t get_level(buddy_allocator_t *buddy_allocator, size_t sz) {
    uint8_t actual_level = buddy_allocator->depth - 1;
    size_t actual_size = buddy_allocator->min_node_size;
    while (actual_size < sz) {
        actual_level--;
        actual_size *= 2;
    }
    return actual_level;
}

int64_t get_buddy_idx(buddy_allocator_t *buddy_allocator, uint8_t level) {
    int8_t actual_level = level;
    int64_t idx = -1;
    while (idx == -1 && actual_level >= 0) {
        size_t start = (1 << actual_level) - 1;
        size_t end = (1 << (actual_level + 1)) - 1;
        for (size_t i = start; i < end; i++) {
            if (bit_map_get(buddy_allocator->bit_map, i) == BIT_AVAILABLE) {
                idx = i;
                break;
            }
        }
        actual_level--;
    }
    if (idx == -1) {
        return -1;
    }
    actual_level++;
    bit_map_set(buddy_allocator->bit_map, idx, BIT_USED);
    while (actual_level < level) {
        size_t left_child = get_left_child(idx);
        size_t right_child = get_right_child(idx);
        bit_map_set(buddy_allocator->bit_map, right_child, BIT_AVAILABLE);
        idx = left_child;
        actual_level++;
    }
    return idx;
}

size_t get_buddy_size(buddy_allocator_t *buddy_allocator, uint8_t level) {
    return buddy_allocator->min_node_size * (1 << (buddy_allocator->depth - level - 1));
}

void buddy_allocator_init(buddy_allocator_t *buddy_allocator, void *buffer) {
    buddy_allocator->buffer = buffer;
    buddy_allocator->depth = BUDDY_ALLOCATOR_MAX_LEVELS;
    buddy_allocator->min_node_size = BUDDY_ALLOCATOR_MIN_NODE_SIZE;
    bit_map_init(&bit_map, bit_map_buffer, BIT_MAP_BUFFER_SIZE);
    buddy_allocator->bit_map = &bit_map;
    bit_map_set(buddy_allocator->bit_map, 0, BIT_AVAILABLE);
}

void *buddy_allocator_malloc(buddy_allocator_t *buddy_allocator, size_t sz) {
    uint8_t level = get_level(buddy_allocator, sz + sizeof(size_t));
    int64_t idx = get_buddy_idx(buddy_allocator, level);
    if (idx == -1) {
        fprintf(stderr, "No memory available\n");
        return NULL;
    }
    size_t idx_in_level = idx - ((1 << level) - 1);
    size_t buddy_size = get_buddy_size(buddy_allocator, level);

    size_t *ptr = (size_t *)((uint8_t*)buddy_allocator->buffer + buddy_size * idx_in_level);
    *ptr = (size_t)idx;

    print_bit_map(buddy_allocator->bit_map);

    return (void *)(ptr + 1);
}

void buddy_allocator_free(buddy_allocator_t *buddy_allocator, void *ptr) {
    size_t idx = *((size_t *)ptr - 1);

    printf("freeing idx: %ld\n", idx);
    bit_map_set(buddy_allocator->bit_map, idx, BIT_AVAILABLE);

    while (idx != 0) {
        size_t parent = get_parent(idx);
        size_t left_child = get_left_child(parent);
        size_t right_child = get_right_child(parent);
        if (bit_map_get(buddy_allocator->bit_map, left_child) == BIT_AVAILABLE && bit_map_get(buddy_allocator->bit_map, right_child) == BIT_AVAILABLE) {
            bit_map_set(buddy_allocator->bit_map, parent, BIT_AVAILABLE);
            bit_map_set(buddy_allocator->bit_map, left_child, BIT_USED);
            bit_map_set(buddy_allocator->bit_map, right_child, BIT_USED);
        } else {
            break;
        }
        idx = parent;
    }
    print_bit_map(buddy_allocator->bit_map);
}