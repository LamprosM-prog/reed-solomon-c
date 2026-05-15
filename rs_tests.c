#include "gf.h"
#include "poly.h"
#include "rs_encoder.h"
#include "rs_decode.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main() {
    gf_init();
    uint8_t message[] = {1, 2, 3, 4};
    int msg_len = 4;
    int ecc_len = 4;
    int out_len; //codeword
    int gen_len;

    uint8_t* gen = build(ecc_len, &gen_len);
    uint8_t* codeword = encode(message, gen, msg_len, ecc_len, &out_len);

    printf("Codeword: ");
    for(int i = 0; i < out_len; i++) {
    printf("%d ", codeword[i]);
    }
    printf("\n");
    codeword[5] ^= 0x1F; 
    uint8_t* syndromes = compute_syndromes(codeword, out_len, ecc_len);
    printf("Syndromes : ");
    for(int i = 0; i < 4; i++){
        printf("%d ", syndromes[i]);
    }
    printf("\n");
    printf("Does it have errors? %i", check_errors(syndromes, ecc_len));
   printf("\n");
    int out_lambda_len;
    uint8_t* lambda = berlekamp_massey(syndromes, ecc_len, &out_lambda_len);
    printf("Lambda: ");
    for(int i = 0; i < out_lambda_len; i++){
        printf("%d ", lambda[i]);
    }
    printf("\n");
    int out_len_pos;
    int* error_possitons = chien_search(lambda, out_lambda_len,out_len, &out_len_pos);
    printf("out_len_pos: %d\n", out_len_pos);
    printf("Error magnitudes : ");
    printf("\n");
    for(int i = 0; i < out_len_pos; i ++){
        printf("%d ", error_possitons[i]);
    }
    printf("\n");
    uint8_t* corrected_codeword = forney(lambda, out_lambda_len, syndromes, ecc_len, codeword, out_len, error_possitons, out_len_pos);
    printf("Corrected codeword: ");
    for(int i=0; i< out_len; i++){ 
        printf("%d ", corrected_codeword[i]);
    }
    printf("\n");
    
    free(error_possitons);
    free(syndromes);
    free(lambda);
    free(gen);
    free(codeword);

return 0;
}