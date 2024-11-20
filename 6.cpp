#include <stdio.h>
#include <ctype.h>
#include <string.h>

int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

void decrypt_affine(char ciphertext[], int a, int b) {
    int a_inv = mod_inverse(a, 26); 
    if (a_inv == -1) {
        printf("Modular inverse of a doesn't exist.\n");
        return;
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int c = toupper(ciphertext[i]) - 'A';
            int p = (a_inv * (c - b + 26)) % 26;
            ciphertext[i] = isupper(ciphertext[i]) ? 'A' + p : 'a' + p;
        }
    }
}

int main() {
    char ciphertext[100];
    int a = 3, b = 15; 

    printf("Enter ciphertext: ");
    scanf("%s", ciphertext);

    decrypt_affine(ciphertext, a, b);

    printf("Decrypted text: %s\n", ciphertext);
    return 0;
}

