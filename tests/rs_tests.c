#include "../src/gf.h"
#include "../src/poly.h"
#include "../src/rs_encoder.h"
#include "../src/rs_decode.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
    gf_init();

    // k=800 symbols (1600 bytes), n=1600 symbols (3200 bytes), ecc=800 symbols
    int msg_len = 800;   // symbols
    int ecc_len = 800;   // symbols
    int out_len;
    int gen_len;

    // build message: 784 real symbols (c1+c2+e+s) + 16 padding
    uint16_t* message = calloc(msg_len, sizeof(uint16_t));
    // fill with dummy payload — 32 bytes of "raw data" spread across fields
    for (int i = 0; i < msg_len; i++) {
        message[i] = (uint16_t)(i + 1);  // just recognizable test values
    }

    uint16_t* gen = build(ecc_len, &gen_len);
    uint16_t* codeword = encode(message, gen, msg_len, ecc_len, &out_len);

    printf("Codeword length: %d symbols (%d bytes)\n", out_len, out_len * 2);

    // inject 350 errors at evenly spaced positions
    int error_count = 350;
    int* injected = malloc(error_count * sizeof(int));
    for (int i = 0; i < error_count; i++) {
        int pos = (i * out_len) / error_count;  
        injected[i] = pos;
        codeword[pos] ^= 0x1234;                // corrupt with known pattern
    }

    printf("Injected %d errors\n", error_count);

    // syndromes
    uint16_t* syndromes = compute_syndromes(codeword, out_len, ecc_len);
    printf("Has errors: %d\n", check_errors(syndromes, ecc_len));

    // berlekamp-massey
    int lambda_len;
    uint16_t* lambda = berlekamp_massey(syndromes, ecc_len, &lambda_len);
    printf("Lambda degree: %d\n", lambda_len - 1);

    // chien search
    int found_count;
    int* error_positions = chien_search(lambda, lambda_len, out_len, &found_count);
    printf("Errors found by Chien: %d\n", found_count);

    // forney + correction
    uint16_t* corrected = forney(lambda, lambda_len, syndromes, ecc_len,
                                  codeword, out_len, error_positions, found_count);

    // verify against original
    int ok = 1;
    for (int i = 0; i < msg_len; i++) {
        if (corrected[i] != message[i]) {
            printf("MISMATCH at symbol %d: got %d expected %d\n",
                   i, corrected[i], message[i]);
            ok = 0;
        }
    }
    if (ok) printf("All %d message symbols recovered correctly.\n", msg_len);

    free(injected);
    free(error_positions);
    free(syndromes);
    free(lambda);
    free(gen);
    free(codeword);
    free(message);

    return 0;
}