#include "bit_map.h"

#include <string.h>
#include <stdio.h>

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
    // used with low depth values
    size_t pow = 1;
    size_t cnt = pow;
    for (size_t i = 0; i < 8 * bit_map->size; i++) {
        if (cnt == 0) {
            printf("\n");
            pow *= 2;
            cnt = pow;
        }
        printf("%d", bit_map_get(bit_map, i));
        cnt--;
    }
}