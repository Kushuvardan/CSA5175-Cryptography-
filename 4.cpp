#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char plaintext[], char key[]) {
    int n = strlen(plaintext), m = strlen(key), i, shift;
    for (i = 0; i < n; i++) {
        if (isalpha(plaintext[i])) {
            shift = toupper(key[i % m]) - 'A';
            plaintext[i] = isupper(plaintext[i]) 
                ? 'A' + (plaintext[i] - 'A' + shift) % 26 
                : 'a' + (plaintext[i] - 'a' + shift) % 26;
        }
    }
}

int main() {
    char plaintext[100], key[100];
    printf("Enter plaintext: ");
    scanf("%s", plaintext);
    printf("Enter key: ");
    scanf("%s", key);
    encrypt(plaintext, key);
    printf("Ciphertext: %s\n", plaintext);
    return 0;
}

