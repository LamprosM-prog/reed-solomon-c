#ifndef RS_ENCODER
#define RS_ENCODER

#include <stdint.h>

uint8_t*  build(int eccLength, int* out_len);
uint8_t*  encode(uint8_t* message,uint8_t* gen_poly, int msg_len, int eccLength, int* out_len);
#endif  