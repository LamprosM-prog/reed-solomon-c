#include <stdint.h>
#include "rs_decode.h"
#include "gf.h"
#include "poly.h"
#include <stdlib.h>


uint8_t* compute_syndromes(uint8_t* codeword, int codeword_len, int ecc_len){
    uint8_t*  syndromes = malloc(ecc_len);
    for(int i = 0; i < ecc_len; i++ ){
        uint8_t x = gf_generator(i+1); //prime element
        uint8_t result = 0;
        for(int j = 0; j < codeword_len; j++){
            result = gf_add(gf_multiply(result, x), codeword[j]);
        }
        syndromes[i] = result;
    }
    return syndromes;
}

int check_errors(uint8_t* syndromes, int ecc_len){
    for(int i = 0; i < ecc_len; i++){
        if(syndromes[i] != 0) return 1;
    }
    return 0;
}