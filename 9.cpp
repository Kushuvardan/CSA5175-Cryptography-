#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5

char matrix[MATRIX_SIZE][MATRIX_SIZE];

void createMatrix(char keyword[]) {
    int used[26] = {0};
    used['J' - 'A'] = 1;
    int idx = 0;
    for (int i = 0; keyword[i] != '\0'; i++) {
        char c = toupper(keyword[i]);
        if (!used[c - 'A']) {
            matrix[idx / MATRIX_SIZE][idx % MATRIX_SIZE] = c;
            used[c - 'A'] = 1;
            idx++;
        }
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            matrix[idx / MATRIX_SIZE][idx % MATRIX_SIZE] = c;
            idx++;
        }
    }
}

void findPosition(char c, int *row, int *col) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void decryptPair(char a, char b, char *result) {
    int row1, col1, row2, col2;
    findPosition(a, &row1, &col1);
    findPosition(b, &row2, &col2);
    if (row1 == row2) {
        result[0] = matrix[row1][(col1 + MATRIX_SIZE - 1) % MATRIX_SIZE];
        result[1] = matrix[row2][(col2 + MATRIX_SIZE - 1) % MATRIX_SIZE];
    } else if (col1 == col2) {
        result[0] = matrix[(row1 + MATRIX_SIZE - 1) % MATRIX_SIZE][col1];
        result[1] = matrix[(row2 + MATRIX_SIZE - 1) % MATRIX_SIZE][col2];
    } else {
        result[0] = matrix[row1][col2];
        result[1] = matrix[row2][col1];
    }
}

int main() {
    char keyword[100], ciphertext[200], plaintext[200];
    scanf("%s", keyword);
    scanf("%s", ciphertext);
    createMatrix(keyword);
    int len = strlen(ciphertext);
    char result[2];
    for (int i = 0; i < len; i += 2) {
        decryptPair(toupper(ciphertext[i]), toupper(ciphertext[i + 1]), result);
        plaintext[i] = result[0];
        plaintext[i + 1] = result[1];
    }
    plaintext[len] = '\0';
    printf("%s\n", plaintext);
    return 0;
}

