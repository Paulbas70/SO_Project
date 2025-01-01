#include "bit_map.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

int main() {
    printf("Starting simple bit_map test...\n");

    uint8_t buffer[1];
    bit_map_t bit_map;

    bit_map_init(&bit_map, buffer, sizeof(buffer));

    for (size_t i = 0; i < 8; i++) {
        bool bit = bit_map_get(&bit_map, i);
        assert(bit == BIT_USED);
    }
    printf("Initialization: All bits are BIT_USED as expected.\n");

    size_t set_idx = 3;
    bit_map_set(&bit_map, set_idx, BIT_AVAILABLE);
    bool bit = bit_map_get(&bit_map, set_idx);
    assert(bit == BIT_AVAILABLE);
    printf("Set Bit %zu to BIT_AVAILABLE: Success.\n", set_idx);

    for (size_t i = 0; i < 8; i++) {
        if (i == set_idx) continue;
        bool current_bit = bit_map_get(&bit_map, i);
        assert(current_bit == BIT_USED);
    }
    printf("Other bits remain BIT_USED: Success.\n");

    bit_map_set(&bit_map, set_idx, BIT_USED);
    bit = bit_map_get(&bit_map, set_idx);
    assert(bit == BIT_USED);
    printf("Reset Bit %zu to BIT_USED: Success.\n", set_idx);

    size_t first_idx = 0;
    size_t last_idx = 7;

    bit_map_set(&bit_map, first_idx, BIT_AVAILABLE);
    assert(bit_map_get(&bit_map, first_idx) == BIT_AVAILABLE);
    printf("Set first Bit %zu to BIT_AVAILABLE: Success.\n", first_idx);

    bit_map_set(&bit_map, last_idx, BIT_AVAILABLE);
    assert(bit_map_get(&bit_map, last_idx) == BIT_AVAILABLE);
    printf("Set last Bit %zu to BIT_AVAILABLE: Success.\n", last_idx);

    bit_map_set(&bit_map, first_idx, BIT_USED);
    bit_map_set(&bit_map, last_idx, BIT_USED);
    assert(bit_map_get(&bit_map, first_idx) == BIT_USED);
    assert(bit_map_get(&bit_map, last_idx) == BIT_USED);
    printf("Reset first and last bits to BIT_USED: Success.\n");

    printf("All bit_map tests passed successfully.\n");

    return 0;
}
