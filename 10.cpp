#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void findPos(char c, int *row, int *col) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (matrix[i][j] == c || (c == 'J' && matrix[i][j] == 'I')) {
                *row = i;
                *col = j;
                return;
            }
}

void encryptPair(char a, char b, char *result) {
    int r1, c1, r2, c2;
    findPos(a, &r1, &c1);
    findPos(b, &r2, &c2);

    if (r1 == r2) {
        result[0] = matrix[r1][(c1 + 1) % 5];
        result[1] = matrix[r2][(c2 + 1) % 5];
    } else if (c1 == c2) {
        result[0] = matrix[(r1 + 1) % 5][c1];
        result[1] = matrix[(r2 + 1) % 5][c2];
    } else {
        result[0] = matrix[r1][c2];
        result[1] = matrix[r2][c1];
    }
}

void preprocess(char *input, char *output) {
    int len = 0;
    for (int i = 0; input[i]; i++)
        if (isalpha(input[i]))
            output[len++] = toupper(input[i] == 'J' ? 'I' : input[i]);
    output[len] = '\0';

    for (int i = 0; i < len; i += 2) {
        if (output[i + 1] == '\0') {
            output[i + 1] = 'X';
            output[i + 2] = '\0';
        } else if (output[i] == output[i + 1]) {
            memmove(&output[i + 1], &output[i], strlen(&output[i]) + 1);
            output[i + 1] = 'X';
        }
    }
}

int main() {
    char message[100], processed[100], encrypted[100];
    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);

    preprocess(message, processed);

    int len = strlen(processed);
    for (int i = 0; i < len; i += 2)
        encryptPair(processed[i], processed[i + 1], &encrypted[i]);

    encrypted[len] = '\0';
    printf("Encrypted message: %s\n", encrypted);
    return 0;
}

