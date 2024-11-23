#include <stdio.h>
#include <stdint.h>
#include <gmp.h>

void generate_rsa_keys(mpz_t e, mpz_t d, mpz_t n, mpz_t p, mpz_t q) {
    // RSA Key generation with a given p and q
    mpz_t phi_n;
    mpz_inits(phi_n, NULL);
    
    // Compute n = p * q
    mpz_mul(n, p, q);
    
    // Compute f(n) = (p-1)*(q-1)
    mpz_t p_minus_1, q_minus_1;
    mpz_inits(p_minus_1, q_minus_1, NULL);
    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);
    mpz_mul(phi_n, p_minus_1, q_minus_1);
    
    // Select public exponent e (Common choice is 65537)
    mpz_set_ui(e, 65537);
    
    // Compute private key d, such that d = e^(-1) mod f(n)
    mpz_invert(d, e, phi_n);
    
    mpz_clears(phi_n, p_minus_1, q_minus_1, NULL);
}

int main() {
    mpz_t p, q, e, d, n;
    mpz_inits(p, q, e, d, n, NULL);

    mpz_set_str(p, "61", 10);
    mpz_set_str(q, "53", 10);
    
    generate_rsa_keys(e, d, n, p, q);

    gmp_printf("Public Key (e, n): (%Zd, %Zd)\n", e, n);
    gmp_printf("Private Key (d): %Zd\n", d);
    
    mpz_clears(p, q, e, d, n, NULL);
    return 0;
}
