#include <stdio.h>
#include <math.h>

int main() {
    int n = 25;
    double factorial_log2 = 0;

    for (int i = 1; i <= n; i++) {
        factorial_log2 += log2(i);  
    }

    printf("Approximate number of possible keys for the Playfair cipher: 2^%.2f\n", factorial_log2);
    return 0;
}

