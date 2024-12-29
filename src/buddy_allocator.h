#pragma once

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

#define BUDDY_ALLOCATOR_MAX_LEVELS 15
#define BUDDY_ALLOCATOR_TOTAL_SIZE (1 << 20)
#define BUDDY_ALLOCATOR_MIN_NODE_SIZE (BUDDY_ALLOCATOR_TOTAL_SIZE >> (BUDDY_ALLOCATOR_MAX_LEVELS - 1))
#define BIT_MAP_BUFFER_SIZE (1 << (BUDDY_ALLOCATOR_MAX_LEVELS + 1))