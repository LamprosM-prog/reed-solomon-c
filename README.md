# Reed-Solomon Codec in C

A complete Reed-Solomon encoder and decoder implemented from scratch in C, with no external libraries. Built as part of a larger RS + ElGamal protocol project.

## What's implemented

- GF(256) arithmetic — addition, multiplication, division, inverse, via log/exp tables with primitive polynomial `0x11D`
- Polynomial operations — add, multiply, divide (remainder), evaluate (Horner's method), formal derivative, trim
- RS Encoder — generator polynomial construction, systematic encoding via polynomial remainder
- RS Decoder — full pipeline:
  - Syndrome computation
  - Berlekamp-Massey (error locator polynomial)
  - Chien Search (error positions)
  - Forney's Algorithm (error magnitudes + correction)

## Example

64-byte message, 3 byte errors introduced, all corrected:

```
Codeword:   1 2 3 4 222 90 167 186 ... (64 message bytes + ECC)
Corrupted:  positions 1, 2, 5 flipped
Corrected:  1 2 3 4 222 90 167 186 ... (original recovered exactly)
```

## Build

```bash
gcc gf.c poly.c rs_encoder.c rs_decode.c rs_tests.c -o rs_tests
./rs_tests
```

## Design notes

All polynomials use **highest-degree-first** convention (index 0 = leading term), consistent across encoder, decoder, and polynomial arithmetic. Berlekamp-Massey builds the error locator polynomial lowest-first internally and reverses before returning, matching the convention used everywhere else.

## Part of

This codec is the error-correction layer of a larger protocol combining Reed-Solomon with ElGamal encryption over UDP, targeting a real two-machine demonstration.

## License

MIT

