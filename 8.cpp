#include <stdio.h>
#include <string.h>
#include <ctype.h>
void generate_cipher(char keyword[], char cipher[]) {
    int used[26] = {0};
    int index = 0;
    for (int i = 0; keyword[i] != '\0'; i++) {
        char c = toupper(keyword[i]);
        if (!used[c - 'A']) {
            cipher[index++] = c;
            used[c - 'A'] = 1;
        }
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            cipher[index++] = c;
        }
    }
    cipher[index] = '\0';
}
void encrypt(char plaintext[], char cipher[], char ciphertext[]) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int index = plaintext[i] - base;
            ciphertext[i] = isupper(plaintext[i]) ? cipher[index] : tolower(cipher[index]);
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}
int main() {
    char keyword[100], plaintext[100], ciphertext[100], cipher[26];
    printf("Enter the keyword: ");
    scanf("%s", keyword);
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);
    generate_cipher(keyword, cipher);
    encrypt(plaintext, cipher, ciphertext);
    printf("Cipher sequence: %s\n", cipher);
    printf("Encrypted text: %s\n", ciphertext);
    return 0;
}

