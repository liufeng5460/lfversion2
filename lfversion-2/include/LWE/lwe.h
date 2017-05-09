#ifndef __LWE_H_
#define __LWE_H_

#include <stdint.h>
#include <stdbool.h>
#include "Entropy.h"
#include "global.h"

//bool compare_vectors(uint16_t *a, uint16_t *b);
//uint32_t knuth_yao_smaller_tables_single_number(uint32_t *rnd);
//uint32_t knuth_yao_single_number_optimized(uint32_t *rnd);
//uint32_t knuth_yao_single_number_pmat_optimized();
uint32_t knuth_yao_single_number(Entropy & randomGen, int * sample_in_table);
//void knuth_yao_small(uint16_t a[LWE_M]);
//void knuth_yao_smaller_tables2(uint16_t a[LWE_M]);
void bitreverse2(uint16_t a[LWE_M]);
void knuth_yao2(Entropy & randomGen, uint16_t a[LWE_M]);
//void knuth_yao_shuffled(uint16_t result[LWE_M]);

uint16_t mod(uint32_t a);
//uint32_t compare_simd(uint32_t a_0[128], uint32_t a_1[128], uint32_t large[LWE_M]);
//uint32_t compare_large_simd(uint32_t large_simd[LWE_M / 2], uint32_t large[LWE_M]);
void coefficient_add2(uint16_t out[LWE_M], uint16_t b[LWE_M], uint16_t c[LWE_M]);
void a_gen2(Entropy & randomGen, uint16_t a[]);
void r1_gen2(Entropy & randomGen, uint16_t r1[]);
void r2_gen2(Entropy & randomGen, uint16_t r2[LWE_M]);
void key_gen2(Entropy & randomGen, uint16_t a[LWE_M], uint16_t p[LWE_M], uint16_t r2[LWE_M]);
//void coefficient_mul_add2(uint16_t *result, uint16_t *large1, uint16_t *large2,	uint16_t *large3);
void coefficient_mul2(uint16_t out[LWE_M], uint16_t b[], uint16_t c[]);
void coefficient_sub2(uint16_t result[LWE_M], uint16_t b[LWE_M], uint16_t c[LWE_M]);
//void message_gen2(uint16_t m[LWE_M]);
void RLWE_enc2(Entropy & randomGen, uint16_t a[LWE_M], uint16_t c1[LWE_M], uint16_t c2[LWE_M], uint16_t m[LWE_M], uint16_t p[LWE_M]);
void RLWE_dec2(uint16_t c1[LWE_M], uint16_t c2[LWE_M], uint16_t r2[LWE_M]);
void fwd_ntt2(uint16_t a[]);
void inv_ntt2(uint16_t a[LWE_M]);
void rearrange2(uint16_t a[LWE_M]);
//void get_ntt_random_numbers(uint32_t *large1, uint32_t *large2, uint32_t i);
//void get_small_ntt_random_numbers(uint16_t *small1, uint16_t *small2, uint32_t i);
void rearrange_for_final(uint16_t in[LWE_M], uint16_t out[LWE_M]);

#endif /* LWE_H_ */
