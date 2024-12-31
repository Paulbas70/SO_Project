#pragma once

#include "bit_map.h"

#define BUDDY_ALLOCATOR_BUFFER_SIZE (1 << 8)
#define BUDDY_ALLOCATOR_MAX_LEVELS 5
#define BUDDY_ALLOCATOR_MIN_NODE_SIZE (BUDDY_ALLOCATOR_BUFFER_SIZE >> (BUDDY_ALLOCATOR_MAX_LEVELS - 1))

/*
level   size of each node
0       1048576 bytes
1       524288 bytes
2       262144 bytes
[...]
13      128 bytes
14      64 bytes
15      32 bytes
*/

#define BUDDIES (1 << BUDDY_ALLOCATOR_MAX_LEVELS) - 1
#define BIT_MAP_BUFFER_SIZE (BUDDIES + 7) / 8

typedef struct {
    void *buffer;
    size_t min_node_size;
    uint8_t depth;
    bit_map_t *bit_map;
} buddy_allocator_t;

void buddy_allocator_init(buddy_allocator_t *buddy_allocator, void *buffer);

void *buddy_allocator_malloc(buddy_allocator_t *buddy_allocator, size_t sz);

void buddy_allocator_free(buddy_allocator_t *buddy_allocator, void *ptr);