#include <stdio.h>
#include <stdint.h>
#include <gmp.h>

void rsa_encrypt(mpz_t ciphertext, mpz_t message, mpz_t e, mpz_t n) {
    mpz_powm(ciphertext, message, e, n);
}

void rsa_decrypt(mpz_t message, mpz_t ciphertext, mpz_t d, mpz_t n) {
    mpz_powm(message, ciphertext, d, n);
}

int main() {
    mpz_t e, d, n;
    mpz_inits(e, d, n, NULL);
    mpz_set_str(e, "65537", 10);
    mpz_set_str(n, "3233", 10);
    mpz_set_str(d, "2753", 10);

    char plaintext[] = "HELLO";
    mpz_t message, ciphertext;
    mpz_inits(message, ciphertext, NULL);

    for (int i = 0; plaintext[i] != '\0'; i++) {
        mpz_set_ui(message, plaintext[i] - 'A');
        rsa_encrypt(ciphertext, message, e, n);
        gmp_printf("Encrypted: %Zd\n", ciphertext);

        mpz_set_ui(message, 0);
        rsa_decrypt(message, ciphertext, d, n);
        gmp_printf("Decrypted: %c\n", (char)(mpz_get_ui(message) + 'A'));
    }

    mpz_clears(e, d, n, message, ciphertext, NULL);
    return 0;
}
