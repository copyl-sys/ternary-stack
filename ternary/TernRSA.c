/*
 * Ternary RSA Implementation for Linux
 *
 * Implements RSA using ternary arithmetic with T81BigInt
 */

#include "ternary_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Compute GCD of two ternary numbers */
static T81BigInt *t81bigint_gcd(const T81BigInt *a, const T81BigInt *b) {
    T81BigInt *x = t81bigint_from_int(t81bigint_to_int(a, NULL));
    T81BigInt *y = t81bigint_from_int(t81bigint_to_int(b, NULL));
    T81BigInt *temp;
    while (t81bigint_to_int(y, NULL) != 0) {
        temp = t81bigint_mod(x, y);
        free_t81bigint(x);
        x = y;
        y = temp;
    }
    free_t81bigint(y);
    return x;
}

/* Compute modular exponentiation (base^exp % mod) */
static T81BigInt *t81bigint_mod_exp(const T81BigInt *base, const T81BigInt *exp, const T81BigInt *mod) {
    T81BigInt *res = t81bigint_from_int(1);
    T81BigInt *b = t81bigint_copy(base);
    T81BigInt *e = t81bigint_copy(exp);
    while (t81bigint_to_int(e, NULL) > 0) {
        if (e->digits[0] % 3 != 0) {
            T81BigInt *temp = t81bigint_mod(t81bigint_mul(res, b), mod);
            free_t81bigint(res);
            res = temp;
        }
        T81BigInt *temp_b = t81bigint_mod(t81bigint_mul(b, b), mod);
        free_t81bigint(b);
        b = temp_b;
        e = t81bigint_div(e, t81bigint_from_int(3));
    }
    free_t81bigint(b);
    free_t81bigint(e);
    return res;
}

/* Generate ternary RSA key pair */
void ternary_rsa_generate_keys(T81BigInt **public_key, T81BigInt **private_key, T81BigInt **modulus) {
    srand(time(NULL));
    T81BigInt *p = t81bigint_from_int(3 + rand() % 81);
    T81BigInt *q = t81bigint_from_int(3 + rand() % 81);
    *modulus = t81bigint_mul(p, q);
    T81BigInt *phi = t81bigint_mul(t81bigint_sub(p, t81bigint_from_int(1)), t81bigint_sub(q, t81bigint_from_int(1)));
    *public_key = t81bigint_from_int(27);
    while (t81bigint_to_int(t81bigint_gcd(*public_key, phi), NULL) != 1) {
        *public_key = t81bigint_from_int(3 + rand() % 81);
    }
    *private_key = t81bigint_mod_exp(*public_key, t81bigint_from_int(-1), phi);
    free_t81bigint(p);
    free_t81bigint(q);
    free_t81bigint(phi);
}

/* Encrypt a ternary message using RSA */
T81BigInt *ternary_rsa_encrypt(const T81BigInt *message, const T81BigInt *public_key, const T81BigInt *modulus) {
    return t81bigint_mod_exp(message, public_key, modulus);
}

/* Decrypt a ternary message using RSA */
T81BigInt *ternary_rsa_decrypt(const T81BigInt *cipher, const T81BigInt *private_key, const T81BigInt *modulus) {
    return t81bigint_mod_exp(cipher, private_key, modulus);
}

int main() {
    T81BigInt *public_key, *private_key, *modulus;
    ternary_rsa_generate_keys(&public_key, &private_key, &modulus);
    printf("Public Key: %d\n", t81bigint_to_int(public_key, NULL));
    printf("Private Key: %d\n", t81bigint_to_int(private_key, NULL));
    printf("Modulus: %d\n", t81bigint_to_int(modulus, NULL));
    
    T81BigInt *message = t81bigint_from_int(5);
    T81BigInt *encrypted = ternary_rsa_encrypt(message, public_key, modulus);
    printf("Encrypted: %d\n", t81bigint_to_int(encrypted, NULL));
    T81BigInt *decrypted = ternary_rsa_decrypt(encrypted, private_key, modulus);
    printf("Decrypted: %d\n", t81bigint_to_int(decrypted, NULL));
    
    free_t81bigint(public_key);
    free_t81bigint(private_key);
    free_t81bigint(modulus);
    free_t81bigint(message);
    free_t81bigint(encrypted);
    free_t81bigint(decrypted);
    return 0;
}
