#include <stdio.h>
#include <stdint.h>

void keyGeneration(uint64_t key, uint64_t subkeys[16]);
uint64_t desDecrypt(uint64_t ciphertext, uint64_t subkeys[16]);
uint64_t initialPermutation(uint64_t input);
uint64_t finalPermutation(uint64_t input);
uint32_t feistel(uint32_t right, uint64_t subkey);

const int shiftSchedule[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

const int PC1[] = { /* ... 56 elements ... */ };
const int PC2[] = { /* ... 48 elements ... */ };
const int IP[] = { /* ... 64 elements ... */ };
const int IP_INV[] = { /* ... 64 elements ... */ };

int main() {
    uint64_t ciphertext = 0x85E813540F0AB405; 
    uint64_t key = 0x133457799BBCDFF1;       
    uint64_t subkeys[16];

    keyGeneration(key, subkeys);

    uint64_t plaintext = desDecrypt(ciphertext, subkeys);

    printf("Decrypted Plaintext: %016llX\n", plaintext);
    return 0;
}

void keyGeneration(uint64_t key, uint64_t subkeys[16]) {
    uint64_t permutedKey = 0; 
    uint32_t C = (permutedKey >> 28) & 0xFFFFFFF;
    uint32_t D = permutedKey & 0xFFFFFFF;         

    for (int i = 0; i < 16; i++) {
        C = (C << shiftSchedule[i]) | (C >> (28 - shiftSchedule[i]));
        D = (D << shiftSchedule[i]) | (D >> (28 - shiftSchedule[i]));

        uint64_t CD = ((uint64_t)C << 28) | D;
        subkeys[i] = 0; 
    }

    for (int i = 0; i < 8; i++) {
        uint64_t temp = subkeys[i];
        subkeys[i] = subkeys[15 - i];
        subkeys[15 - i] = temp;
    }
}

uint64_t desDecrypt(uint64_t ciphertext, uint64_t subkeys[16]) {
    uint64_t permutedText = initialPermutation(ciphertext);
    uint32_t L = permutedText >> 32;
    uint32_t R = permutedText & 0xFFFFFFFF;

    for (int i = 0; i < 16; i++) {
        uint32_t temp = R;
        R = L ^ feistel(R, subkeys[i]);
        L = temp;
    }

    uint64_t combined = ((uint64_t)R << 32) | L;
    return finalPermutation(combined);
}

uint64_t initialPermutation(uint64_t input) {
    uint64_t output = 0;
    for (int i = 0; i < 64; i++) {
        output |= ((input >> (64 - IP[i])) & 1) << (63 - i);
    }
    return output;
}

uint64_t finalPermutation(uint64_t input) {
    uint64_t output = 0;
    for (int i = 0; i < 64; i++) {
        output |= ((input >> (64 - IP_INV[i])) & 1) << (63 - i);
    }
    return output;
}

uint32_t feistel(uint32_t right, uint64_t subkey) {
    uint32_t expanded = 0; 
    uint32_t substituted = 0; 
    uint32_t permuted = 0; 
    return permuted;
}

