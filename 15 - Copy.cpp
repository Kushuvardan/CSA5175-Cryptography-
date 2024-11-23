#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char frequencyOrder[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
#define ALPHABET_SIZE 26

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

void decrypt(char *ciphertext, int key, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - offset - key + ALPHABET_SIZE) % ALPHABET_SIZE + offset;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

void displayTopPlaintexts(char *ciphertext, char *ranked, int topN) {
    char plaintext[1000];
    printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN && i < ALPHABET_SIZE; i++) {
        int key = (ranked[i] - 'A' - ('E' - 'A') + ALPHABET_SIZE) % ALPHABET_SIZE;
        decrypt(ciphertext, key, plaintext);
        printf("Key %d: %s\n", key, plaintext);
    }
}

int main() {
    char ciphertext[1000];
    int topN;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the number of top plaintexts to display: ");
    scanf("%d", &topN);

    int freq[ALPHABET_SIZE];
    calculateFrequency(ciphertext, freq);

    char ranked[ALPHABET_SIZE];
    rankLetters(freq, ranked);

    displayTopPlaintexts(ciphertext, ranked, topN);

    return 0;
}

