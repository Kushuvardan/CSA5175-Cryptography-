#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/des.h>

#define BLOCK_SIZE 8  

void tripleDES_CBC_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key1, uint8_t *key2, uint8_t *key3, uint8_t *iv, size_t length) {
    DES_key_schedule ks1, ks2, ks3;
    DES_cblock ivec;
    memcpy(ivec, iv, BLOCK_SIZE);

    DES_set_key_unchecked((DES_cblock *)key1, &ks1);
    DES_set_key_unchecked((DES_cblock *)key2, &ks2);
    DES_set_key_unchecked((DES_cblock *)key3, &ks3);

    size_t num_blocks = length / BLOCK_SIZE;

    for (size_t i = 0; i < num_blocks; i++) {
        uint8_t block[BLOCK_SIZE];
        memcpy(block, plaintext + i * BLOCK_SIZE, BLOCK_SIZE);

        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] ^= ivec[j];
        }

        uint8_t intermediate[BLOCK_SIZE];
        DES_ecb3_encrypt((DES_cblock *)block, (DES_cblock *)intermediate, &ks1, &ks2, &ks3, DES_ENCRYPT);
        
        memcpy(ciphertext + i * BLOCK_SIZE, intermediate, BLOCK_SIZE);
        memcpy(ivec, intermediate, BLOCK_SIZE);
    }
}

int main() {
    uint8_t plaintext[] = "This is a test message for 3DES CBC mode!";
    size_t length = strlen((char *)plaintext);
    
    uint8_t ciphertext[64];  
    uint8_t key1[8] = {0x13, 0x24, 0x35, 0x46, 0x57, 0x68, 0x79, 0x9A};  
    uint8_t key2[8] = {0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0x07, 0x18};  
    uint8_t key3[8] = {0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F, 0x7A, 0x8B};  
    uint8_t iv[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};  

    tripleDES_CBC_encrypt(plaintext, ciphertext, key1, key2, key3, iv, length);

    printf("Ciphertext: ");
    for (size_t i = 0; i < length; i++) {
        printf("%02X", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

