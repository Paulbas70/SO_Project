#pragma once

#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint8_t *buffer;
    size_t size;
} bit_map_t;

void bit_map_init(bit_map_t *bit_map, uint8_t *buffer, size_t size);