#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

const char englishFrequency[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

void calculateFrequency(char *ciphertext, int freq[]) {
    for (int i = 0; i < ALPHABET_SIZE; i++) freq[i] = 0;
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            freq[toupper(ciphertext[i]) - 'A']++;
        }
    }
}

void rankLetters(int freq[], char ranked[]) {
    int sorted[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) sorted[i] = freq[i];

    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (sorted[i] < sorted[j]) {
                int temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }

    int used[ALPHABET_SIZE] = {0};
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if (!used[j] && freq[j] == sorted[i]) {
                ranked[i] = 'A' + j;
                used[j] = 1;
                break;
            }
        }
    }
}

void decrypt(char *ciphertext, char *key, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char isUpper = isupper(ciphertext[i]);
            char c = toupper(ciphertext[i]);
            int index = strchr(key, c) - key;
            plaintext[i] = isUpper ? ('A' + index) : ('a' + index);
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

void displayTopPlaintexts(char *ciphertext, char *ranked, int topN) {
    char key[ALPHABET_SIZE + 1];
    char plaintext[1000];
    printf("Top %d possible plaintexts:\n", topN);

    for (int i = 0; i < topN && i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            key[ranked[j] - 'A'] = englishFrequency[j];
        }
        key[ALPHABET_SIZE] = '\0';

        decrypt(ciphertext, key, plaintext);
        printf("Key %d: %s\n", i + 1, plaintext);
    }
}

int main() {
    char ciphertext[1000];
    int topN;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 

    printf("Enter the number of top plaintexts to display: ");
    scanf("%d", &topN);

    int freq[ALPHABET_SIZE];
    calculateFrequency(ciphertext, freq);

    char ranked[ALPHABET_SIZE];
    rankLetters(freq, ranked);

    displayTopPlaintexts(ciphertext, ranked, topN);

    return 0;
}

