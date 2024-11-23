#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MOD 26

void encrypt(const char *plaintext, const int key[2][2], char *ciphertext) {
    int i, x, y;
    int length = strlen(plaintext);

    for (i = 0; i < length; i += 2) {
        x = plaintext[i] - 'a';
        y = plaintext[i + 1] - 'a';

        ciphertext[i] = ((key[0][0] * x + key[0][1] * y) % MOD) + 'a';
        ciphertext[i + 1] = ((key[1][0] * x + key[1][1] * y) % MOD) + 'a';
    }
    ciphertext[length] = '\0';
}

int modular_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

void decrypt(const char *ciphertext, const int key[2][2], char *plaintext) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0] + MOD) % MOD;
    int det_inv = modular_inverse(det, MOD);

    int inv_key[2][2] = {
        {key[1][1] * det_inv % MOD, -key[0][1] * det_inv % MOD},
        {-key[1][0] * det_inv % MOD, key[0][0] * det_inv % MOD}
    };

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            inv_key[i][j] = (inv_key[i][j] + MOD) % MOD;

    int i, x, y;
    int length = strlen(ciphertext);

    for (i = 0; i < length; i += 2) {
        x = ciphertext[i] - 'a';
        y = ciphertext[i + 1] - 'a';

        plaintext[i] = ((inv_key[0][0] * x + inv_key[0][1] * y) % MOD) + 'a';
        plaintext[i + 1] = ((inv_key[1][0] * x + inv_key[1][1] * y) % MOD) + 'a';
    }
    plaintext[length] = '\0';
}

int main() {
    char plaintext[] = "meet me";
    char ciphertext[100], decrypted_text[100];

    int key[2][2] = {
        {9, 4},
        {5, 7}
    };

    int length = strlen(plaintext);
    if (length % 2 != 0)
        plaintext[length++] = 'x'; // Padding for odd length
    plaintext[length] = '\0';

    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    decrypt(ciphertext, key, decrypted_text);
    printf("Decrypted Text: %s\n", decrypted_text);

    return 0;
}

