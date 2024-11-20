#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void createMatrix(char key[], char matrix[SIZE][SIZE]) {
    int used[26] = {0}, k = 0;
    used['J' - 'A'] = 1;
    for (int i = 0; key[i] || k < 25; i++) {
        char c = (key[i] ? toupper(key[i]) : 'A' + k++);
        if (c == 'J') c = 'I';
        if (isalpha(c) && !used[c - 'A']) matrix[k / SIZE][k % SIZE] = c, used[c - 'A'] = 1;
    }
}

void encrypt(char text[], char matrix[SIZE][SIZE]) {
    for (int i = 0; text[i]; i += 2) {
        int r1, c1, r2, c2, j = (text[i] == 'J') ? 'I' : text[i];
        for (r1 = 0; r1 < SIZE && !c1; r1++) for (c1 = 0; c1 < SIZE; c1++) if (matrix[r1][c1] == j) break;
        for (r2 = 0; r2 < SIZE && !c2; r2++) for (c2 = 0; c2 < SIZE; c2++) if (matrix[r2][c2] == text[i + 1]) break;
        text[i] = matrix[r1][(c1 + 1) % SIZE], text[i + 1] = matrix[r2][(c2 + 1) % SIZE];
    }
}

int main() {
    char key[30], text[100], matrix[SIZE][SIZE];
    scanf("%s%s", key, text);
    createMatrix(key, matrix);
    encrypt(text, matrix);
    printf("%s\n", text);
}
