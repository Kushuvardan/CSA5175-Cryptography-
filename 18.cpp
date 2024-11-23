#include <stdio.h>
#include <stdint.h>

const int shiftSchedule[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

void keyGeneration(uint64_t key, uint64_t subkeys[16]);

int main() {
    uint64_t key = 0x133457799BBCDFF1; 
    uint64_t subkeys[16];

    keyGeneration(key, subkeys);

    for (int i = 0; i < 16; i++) {
        printf("Subkey %2d: %012llX\n", i + 1, subkeys[i]);
    }

    return 0;
}

void keyGeneration(uint64_t key, uint64_t subkeys[16]) {
    const int PC1[] = { /* 56 elements mapping from 64-bit key to 56-bit key */ };

    uint32_t A = 0, B = 0;

    for (int i = 0; i < 56; i++) {
        if (i < 28) {
            A = (A << 1) | ((key >> (64 - PC1[i])) & 1);
        } else {
            B = (B << 1) | ((key >> (64 - PC1[i])) & 1);
        }
    }

    for (int round = 0; round < 16; round++) {
        int shifts = shiftSchedule[round];
        A = ((A << shifts) | (A >> (28 - shifts))) & 0xFFFFFFF;
        B = ((B << shifts) | (B >> (28 - shifts))) & 0xFFFFFFF;

        uint32_t A_part = A >> 4; 
        uint32_t B_part = B >> 4; 

        subkeys[round] = ((uint64_t)A_part << 24) | B_part;
    }
}

