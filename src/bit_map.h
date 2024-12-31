#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BIT_USED 0
#define BIT_AVAILABLE 1

typedef struct {
    uint8_t *buffer;
    size_t size;
} bit_map_t;

void bit_map_init(bit_map_t *bit_map, uint8_t *buffer, size_t size);

void bit_map_set(bit_map_t *bit_map, size_t idx, bool value);

bool bit_map_get(bit_map_t *bit_map, size_t idx);

void print_bit_map(bit_map_t *bit_map);