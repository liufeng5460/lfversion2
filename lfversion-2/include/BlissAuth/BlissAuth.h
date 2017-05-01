#ifndef BLISSSIG_H_INCLUDED
#define BLISSSIG_H_INCLUDED

#include "KeyGen.h"
#include "Sign.h"

void BlissKeyGen(struct pubkey4io *pk, struct seckey4io *sk);
//公钥和私钥与Bliss签名相同

void Commitment(struct pubkey4io *pk, long u[N]);
//Alice向Bob证明自己的身份，先向Bob发送“承诺”u

void Challenge(unsigned char miu[SHA512_DIGEST_LENGTH]);
//Bob为了验证Alice的身份，向Alice发送“挑战”miu

long Answer(struct pubkey4io *pk, struct seckey4io *sk, struct signature4io *sig, long u[N], unsigned char miu[SHA512_DIGEST_LENGTH]);
//Alice接受Bob的挑战，使用自己的私钥对miu进行签名，Alice需要将签名sig结果和Answer的返回值一起发送给Bob

bool Decision(struct pubkey4io *pk, struct signature4io *sig, long u[N], unsigned char miu[SHA512_DIGEST_LENGTH], long nb_tests);
//Bob的根据Alice的回答和之前的“承诺”u，经过计算决定是否接受Alice的身份

#endif // BLISSSIG_H_INCLUDED
