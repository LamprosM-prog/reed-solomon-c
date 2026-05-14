#include "gf.h"
#include "poly.h"
#include <stdio.h>
#include <stdlib.h>
#include "rs_encoder.h"

int main() {
    gf_init();

    // {x^2 + 2x + 3} + {4x + 5} = x^2 + 6x + 6 (in GF256, 2^4=6, 3^5=6)
    uint8_t a[] = {1, 2, 3};
    uint8_t b[] = {4, 5};
    int out_len1;

    uint8_t* result1 = poly_add(a, 3, b, 2, &out_len1);

    printf("Result Addition length: %d\n", out_len1);
    printf("Result Additon: ");
    for (int i = 0; i < out_len1; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n");



    free(result1);  //caller
    
    // {x^2 + 2x + 3} * {4x + 5} = 4x^3 + 5x^2 + 8x^2 + 12x +10x + 15 = 4x^3 + 13x^2 + 6x + 15 (GF256 : 10 + 22 = 6)
    uint8_t c[] = {1, 2, 3};
    uint8_t d[] = {4, 5};
    int out_len2;

    uint8_t* result2 = poly_multiply(c, 3, d, 2, &out_len2);

    printf("Result Multiplication length: %d\n", out_len2);
    printf("Result Additon: ");
    for (int i = 0; i < out_len2; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n");


    
    free(result2);

    // poly = {1, 2, 3} = x^2 + 2x + 3, evaluate at x=2
    uint8_t poly[] = {1, 2, 3};
    uint8_t eval_result = poly_evaluate(poly, 3, 2);
    printf("Evaluate x^2+2x+3 at x=2: %d\n", eval_result);


    // Test poly_derivative
    // poly = {1, 2, 3, 4} = x^3 + 2x^2 + 3x + 4
    // derivative = 3x^2 + 0x + 3 = {1, 0, 3} (only odd powers survive in GF256)
    int deriv_len; 
    uint8_t poly2[] = {1, 2, 3, 4};
    uint8_t* deriv = poly_derivate(poly2, 4, &deriv_len);
    printf("Derivative length: %d\n", deriv_len); 
    printf("Derivative: ");
    for (int i = 0; i < deriv_len; i++) {
    printf("%d ", deriv[i]);
    }
    printf("\n");
    free(deriv);
    
    uint8_t divident[] = {1, 2, 3, 4};
    uint8_t divisor[] = {1, 1};
    int remainder_len;
    uint8_t* remainder = poly_divide_remainder(divident, 4 , divisor , 2, &remainder_len);
    printf("The length of remainder of (x^3 + 2x^2 + 3x + 4)/(x+1) is: %d\n", remainder_len);
    printf("Remainder : ");
    for (int i = 0; i < remainder_len; i++){
        printf("%d", remainder[i]);
    }
    printf("\n");
    free(remainder);
    printf("%d\n", poly_evaluate(divident, 4, 1));   


    int out_len_gen; 
    uint8_t* gen = build(4, &out_len_gen);
    printf("Gen length = %d\n", out_len_gen);   
    printf("Generator poly:");
    for(int i = 0; i < out_len_gen; i++){
        printf("%d ", gen[i]);
    }
    printf("\n");
    for (int i = 1; i <= 4; i++) {
    printf("%d\n", poly_evaluate(gen, 5, gf_generator(i)));
    }
    uint8_t inv = gf_inverse(8);
    printf("inv(8)=%d, 8*inv(8)=%d\n", inv, gf_multiply(8, inv));


    free(gen);
    return 0;
}