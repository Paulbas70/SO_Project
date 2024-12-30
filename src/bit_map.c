#include "bit_map.h"

void bit_map_init(bit_map_t *bit_map, uint8_t *buffer, size_t size) {
    bit_map->buffer = buffer;
    bit_map->size = size;
    memset(bit_map->buffer, 0, bit_map->size);
}