#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 1024
#define NUM_LANES 16

void initialize_state(uint8_t state[NUM_LANES]) {
    memset(state, 0, NUM_LANES);
}

void absorb_block(uint8_t state[NUM_LANES], uint8_t block[NUM_LANES]) {
    for (int i = 0; i < NUM_LANES; i++) {
        state[i] ^= block[i];
    }
}

int all_lanes_nonzero(uint8_t state[NUM_LANES]) {
    for (int i = 0; i < NUM_LANES; i++) {
        if (state[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    uint8_t state[NUM_LANES];
    uint8_t block[NUM_LANES] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
                                0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

    initialize_state(state);

    int iterations = 0;
    while (!all_lanes_nonzero(state)) {
        absorb_block(state, block);
        iterations++;
    }

    printf("Iterations needed: %d\n", iterations);

    return 0;
}
