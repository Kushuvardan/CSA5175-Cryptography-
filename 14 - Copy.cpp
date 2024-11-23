#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

void encrypt(char plaintext[], int key[], int key_len, char ciphertext[]) {
    int i;
    for (i = 0; i < strlen(plaintext); i++) {
        if (plaintext[i] != ' ') {
            int letter = plaintext[i] - 'a';
            int key_shift = key[i % key_len];
            ciphertext[i] = 'a' + (letter + key_shift) % ALPHABET_SIZE;
        } else {
            ciphertext[i] = ' ';
        }
    }
    ciphertext[i] = '\0';
}

void find_key(char ciphertext[], char plaintext[], int key[], int key_len) {
    int i;
    for (i = 0; i < strlen(plaintext); i++) {
        if (plaintext[i] != ' ') {
            int ciphertext_letter = ciphertext[i] - 'a';
            int plaintext_letter = plaintext[i] - 'a';
            int key_shift = (ciphertext_letter - plaintext_letter + ALPHABET_SIZE) % ALPHABET_SIZE;
            key[i % key_len] = key_shift;
        }
    }
}

int main() {
    char plaintext[] = "send more money";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int key_len = sizeof(key) / sizeof(key[0]);
    char ciphertext[strlen(plaintext) + 1];

    encrypt(plaintext, key, key_len, ciphertext);
    printf("Encrypted Text (Ciphertext): %s\n", ciphertext);

    char new_plaintext[] = "cash not needed";
    int recovered_key[key_len];

    find_key(ciphertext, new_plaintext, recovered_key, key_len);

    printf("Recovered Key Stream: ");
    for (int i = 0; i < key_len; i++) {
        printf("%d ", recovered_key[i]);
    }
    printf("\n");

    return 0;
}

