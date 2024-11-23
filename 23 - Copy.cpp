#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 8

uint8_t sdes_encrypt(uint8_t block, uint8_t key) {
    // Placeholder: actual S-DES encryption logic here
    return block ^ key;
}

void CTR_encrypt(uint8_t* plaintext, uint8_t* ciphertext, uint8_t key, uint8_t counter, size_t length) {
    for (size_t i = 0; i < length; i++) {
        uint8_t keystream = sdes_encrypt(counter++, key);
        ciphertext[i] = plaintext[i] ^ keystream;
    }
}

void CTR_decrypt(uint8_t* ciphertext, uint8_t* plaintext, uint8_t key, uint8_t counter, size_t length) {
    // Decryption is the same as encryption in CTR mode
    for (size_t i = 0; i < length; i++) {
        uint8_t keystream = sdes_encrypt(counter++, key);
        plaintext[i] = ciphertext[i] ^ keystream;
    }
}

int main() {
    uint8_t plaintext[3] = {0x01, 0x02, 0x04};  // 0000 0001 0000 0010 0000 0100
    uint8_t key = 0xFD;                        // 0111 1111 1101
    uint8_t counter = 0x00;                    // 0000 0000
    uint8_t ciphertext[3];
    uint8_t decrypted[3];

    CTR_encrypt(plaintext, ciphertext, key, counter, 3);
    printf("Ciphertext: %02X %02X %02X\n", ciphertext[0], ciphertext[1], ciphertext[2]);

    CTR_decrypt(ciphertext, decrypted, key, counter, 3);
    printf("Decrypted: %02X %02X %02X\n", decrypted[0], decrypted[1], decrypted[2]);

    return 0;
}#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 8

uint8_t sdes_encrypt(uint8_t block, uint8_t key) {
    // Placeholder: actual S-DES encryption logic here
    return block ^ key;
}

void CTR_encrypt(uint8_t* plaintext, uint8_t* ciphertext, uint8_t key, uint8_t counter, size_t length) {
    for (size_t i = 0; i < length; i++) {
        uint8_t keystream = sdes_encrypt(counter++, key);
        ciphertext[i] = plaintext[i] ^ keystream;
    }
}

void CTR_decrypt(uint8_t* ciphertext, uint8_t* plaintext, uint8_t key, uint8_t counter, size_t length) {
    // Decryption is the same as encryption in CTR mode
    for (size_t i = 0; i < length; i++) {
        uint8_t keystream = sdes_encrypt(counter++, key);
        plaintext[i] = ciphertext[i] ^ keystream;
    }
}

int main() {
    uint8_t plaintext[3] = {0x01, 0x02, 0x04};  // 0000 0001 0000 0010 0000 0100
    uint8_t key = 0xFD;                        // 0111 1111 1101
    uint8_t counter = 0x00;                    // 0000 0000
    uint8_t ciphertext[3];
    uint8_t decrypted[3];

    CTR_encrypt(plaintext, ciphertext, key, counter, 3);
    printf("Ciphertext: %02X %02X %02X\n", ciphertext[0], ciphertext[1], ciphertext[2]);

    CTR_decrypt(ciphertext, decrypted, key, counter, 3);
    printf("Decrypted: %02X %02X %02X\n", decrypted[0], decrypted[1], decrypted[2]);

    return 0;
}
