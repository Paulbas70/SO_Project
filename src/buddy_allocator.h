#pragma once

#include "bit_map.h"

#include <stddef.h>

#define BUDDY_ALLOCATOR_BUFFER_SIZE (1 << 20)
#define BUDDY_ALLOCATOR_MIN_NODE_SIZE (BUDDY_ALLOCATOR_BUFFER_SIZE >> (BUDDY_ALLOCATOR_MAX_LEVELS - 1))
#define BUDDY_ALLOCATOR_MAX_LEVELS 15

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

#define BIT_MAP_BUFFER_SIZE (1 << (BUDDY_ALLOCATOR_MAX_LEVELS + 1))

typedef struct {
    void *buffer;
    size_t min_node_size;
    size_t depth;
    bit_map_t *bit_map;
} buddy_allocator_t;

void buddy_allocator_init(buddy_allocator_t *buddy_allocator, void *buffer, bit_map_t *bit_map);

void *buddy_allocator_malloc(size_t sz);

void buddy_allocator_free(void *ptr);