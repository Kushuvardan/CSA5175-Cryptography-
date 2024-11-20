#include <stdio.h>
#include <ctype.h>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void affine_encrypt(char plaintext[], int a, int b) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            int p = toupper(plaintext[i]) - 'A';
            int c = (a * p + b) % 26;
            plaintext[i] = isupper(plaintext[i]) ? 'A' + c : 'a' + c;
        }
    }
}

int main() {
    char plaintext[100];
    int a, b;

    printf("Enter plaintext: ");
    scanf("%s", plaintext);

    printf("Enter values for a and b (ensure gcd(a, 26) = 1): ");
    scanf("%d %d", &a, &b);

    if (gcd(a, 26) != 1) {
        printf("Error: Value of a must be coprime with 26.\n");
        return 1;
    }

    affine_encrypt(plaintext, a, b);

    printf("Encrypted text: %s\n", plaintext);
    return 0;
}

