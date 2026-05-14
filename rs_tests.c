#include "gf.h"
#include "poly.h"
#include "rs_encoder.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main() {
uint8_t message[] = {1, 2, 3, 4};
int msg_len = 4;
int ecc_len = 4;
int out_len;
int gen_len;

uint8_t* gen = build(ecc_len, &gen_len);
uint8_t* codeword = encode(message, gen, msg_len, ecc_len, &out_len);

printf("Codeword: ");
for(int i = 0; i < out_len; i++) {
    printf("%d ", codeword[i]);
}
printf("\n");

free(gen);
free(codeword);

return 0;
}