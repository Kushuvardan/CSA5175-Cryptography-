#include <stdio.h>
#include <stdint.h>
#include <gmp.h>

// Function to find GCD
void gcd(mpz_t result, const mpz_t a, const mpz_t b) {
    mpz_t temp_a, temp_b;
    mpz_inits(temp_a, temp_b, NULL);
    mpz_set(temp_a, a);
    mpz_set(temp_b, b);
    mpz_gcd(result, temp_a, temp_b);
    mpz_clears(temp_a, temp_b, NULL);
}

int main() {
    mpz_t n, e, common_factor;
    mpz_inits(n, e, common_factor, NULL);

    mpz_set_ui(n, 3599);
    mpz_set_ui(e, 31);

    mpz_t plaintext_block;
    mpz_init(plaintext_block);
    mpz_set_ui(plaintext_block, 59); // Example common factor with n

    gcd(common_factor, plaintext_block, n);

    if (mpz_cmp_ui(common_factor, 1) > 0) {
        gmp_printf("Common factor found: %Zd\n", common_factor);
        mpz_t p, q;
        mpz_init(p);
        mpz_init(q);
        mpz_set(p, common_factor);
        mpz_divexact(q, n, p);

        gmp_printf("Factors of n: p = %Zd, q = %Zd\n", p, q);

        mpz_clears(p, q, NULL);
    } else {
        printf("No common factor found.\n");
    }

    mpz_clears(n, e, common_factor,
