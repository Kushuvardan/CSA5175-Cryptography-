#include <stdio.h>
#include <stdint.h>
#include <gmp.h>

// Helper function to perform the Extended Euclidean Algorithm
void extended_euclidean(mpz_t d, const mpz_t e, const mpz_t phi_n) {
    mpz_t s, old_s, t, old_t, r, old_r;
    mpz_inits(s, old_s, t, old_t, r, old_r, NULL);
    mpz_set_ui(s, 0); mpz_set_ui(old_s, 1);
    mpz_set_ui(t, 1); mpz_set_ui(old_t, 0);
    mpz_set(r, phi_n); mpz_set(old_r, e);

    while (mpz_cmp_ui(r, 0) != 0) {
        mpz_t quotient, temp;
        mpz_init(quotient); mpz_init(temp);
        mpz_fdiv_q(quotient, old_r, r);

        mpz_set(temp, r);
        mpz_submul(r, quotient, temp);
        mpz_set(old_r, temp);

        mpz_set(temp, s);
        mpz_submul(s, quotient, temp);
        mpz_set(old_s, temp);

        mpz_set(temp, t);
        mpz_submul(t, quotient, temp);
        mpz_set(old_t, temp);

        mpz_clear(quotient); mpz_clear(temp);
    }

    mpz_set(d, old_s);

    mpz_clears(s, old_s, t, old_t, r, old_r, NULL);
}

int main() {
    mpz_t p, q, n, phi_n, e, d, k;
    mpz_inits(p, q, n, phi_n, e, d, k, NULL);
    mpz_set_ui(p, 59); // Found by trial and error
    mpz_set_ui(q, 61); // Found by trial and error
    mpz_mul(n, p, q); // n = p * q

    mpz_t p_minus_1, q_minus_1;
    mpz_inits(p_minus_1, q_minus_1, NULL);
    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);
    mpz_mul(phi_n, p_minus_1, q_minus_1);

    mpz_set_ui(e, 31);
    extended_euclidean(d, e, phi_n);

    if (mpz_cmp_ui(d, 0) < 0) {
        mpz_add(d, d, phi_n);
    }

    printf("Public Key: (e, n) = (%s, %s)\n", mpz_get_str(NULL, 10, e), mpz_get_str(NULL, 10, n));
    printf("Private Key: d = %s\n", mpz_get_str(NULL, 10, d));

    mpz_clears(p, q, n, phi_n, e, d, k, p_minus_1, q_minus_1, NULL);
    return 0;
}
