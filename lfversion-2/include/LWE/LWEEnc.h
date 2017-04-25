#ifndef LWEENC_H_INCLUDED
#define LWEENC_H_INCLUDED

#include <stdint.h>

#define LWE_M 512

void LWEKeyGen(uint16_t large_a[LWE_M], uint16_t large_p[LWE_M], uint16_t r2[LWE_M]);
// large_a and large_p are the public key.
// r2 is the private Key.
// LWE_M = 512.

void LWEEnc(uint16_t large_a[LWE_M], uint16_t large_p[LWE_M], uint16_t m[LWE_M], uint16_t c1[LWE_M], uint16_t c2[LWE_M]);
// m is the plain text.
// c1 and c2 are the cipher text.

void LWEDec(uint16_t r2[LWE_M], uint16_t c1[LWE_M], uint16_t c2[LWE_M], uint16_t m[LWE_M]);

#endif // LWEENC_H_INCLUDED
