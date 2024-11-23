#include <stdio.h>
#include <stdlib.h>

#define MOD 26

void matrix_multiply(int mat1[2][2], int mat2[2][2], int result[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
            result[i][j] %= MOD;
        }
    }
}

int modular_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

void matrix_inverse(int mat[2][2], int inverse[2][2]) {
    int det = (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]) % MOD;
    if (det < 0)
        det += MOD;

    int det_inv = modular_inverse(det, MOD);
    if (det_inv == -1) {
        printf("Matrix inverse does not exist.\n");
        exit(1);
    }

    inverse[0][0] = (mat[1][1] * det_inv) % MOD;
    inverse[0][1] = (-mat[0][1] * det_inv) % MOD;
    inverse[1][0] = (-mat[1][0] * det_inv) % MOD;
    inverse[1][1] = (mat[0][0] * det_inv) % MOD;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (inverse[i][j] < 0)
                inverse[i][j] += MOD;
        }
    }
}

void find_key(int plaintext[2][2], int ciphertext[2][2], int key[2][2]) {
    int plaintext_inverse[2][2];
    matrix_inverse(plaintext, plaintext_inverse);
    matrix_multiply(plaintext_inverse, ciphertext, key);
}

int main() {
    int plaintext[2][2] = {{7, 4}, {19, 0}}; 
    int ciphertext[2][2] = {{15, 22}, {18, 13}}; 

    int key[2][2];
    find_key(plaintext, ciphertext, key);

    printf("Recovered Key Matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }

    return 0;
}

