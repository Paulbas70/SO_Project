#include "bit_map.h"

#include <string.h>

void bit_map_init(bit_map_t *bit_map, uint8_t *buffer, size_t size) {
    bit_map->buffer = buffer;
    bit_map->size = size;
    memset(bit_map->buffer, BIT_USED, bit_map->size);
}

void bit_map_set(bit_map_t *bit_map, size_t idx, bool value) {
    uint8_t bit = 1 << (idx % 8);
    if (value) {
        bit_map->buffer[idx / 8] |= bit;
    } else {
        bit = ~bit;
        bit_map->buffer[idx / 8] &= bit;
    }
}


bool bit_map_get(bit_map_t *bit_map, size_t idx) {
    uint8_t bit = 1 << (idx % 8);
    return (bit_map->buffer[idx / 8] & bit) != 0;
}

void print_bit_map(bit_map_t *bit_map) {
    for (size_t i = 0; i < bit_map->size; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%d", (bit_map->buffer[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}