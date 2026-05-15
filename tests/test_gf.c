#include "../src/gf.h"
#include <stdio.h>

int main() {
    gf_init();


    printf("5+3 = %d\n", gf_add(5,3)); // 5+3 = 6
    printf("2 * 3 = %d\n", gf_multiply(2,3)); // 2 * 3 = 6
    printf("%d\n", gf_divide(1,0));

    uint8_t a = 50;
    uint8_t inv = gf_inverse(a);
    printf("50 * inv(50) = %d\n", gf_multiply(a,inv)); // a * (1/a) = 1

    printf("6 / 2 = %d\n", gf_divide(6,2)); // 6/2 = 3
    return 0;

}