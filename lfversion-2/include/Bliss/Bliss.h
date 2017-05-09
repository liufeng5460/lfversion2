#ifndef BLISSSIG_H_INCLUDED
#define BLISSSIG_H_INCLUDED

#include "KeyGen.h"
#include "Sign.h"

void BlissKeyGen(struct pubkey4io *pk, struct seckey4io *sk);

void BlissSigM(struct pubkey4io *pk, struct seckey4io *sk, struct signature4io *sig, const std::string message);
bool BlissVerifyM(struct pubkey4io *pk, struct signature4io *sig, const std::string message);

void BlissSigF(struct pubkey4io *pk, struct seckey4io *sk, struct signature4io *sig, const std::string filename);
bool BlissVerifyF(struct pubkey4io *pk, struct signature4io *sig, const std::string filename);

//Alice向Bob证明自己的身份，并发送LWE公钥uint16_t large_a[LWE_M] 和 uint16_t large_p[LWE_M]给Bob

void Challenge(unsigned char miu[SHA512_DIGEST_LENGTH]);
//Bob为了验证Alice的身份，向Alice发送“挑战”miu

void Answer(struct pubkey4io *pk, struct seckey4io *sk, struct signature4io *sig, uint16_t large_a[LWE_M], uint16_t large_p[LWE_M], unsigned char miu[SHA512_DIGEST_LENGTH]);
//Alice接受Bob的挑战，使用自己的私钥对miu和LWE公钥进行签名，Alice将签名sig结果返回值发送给Bob

bool Decision(struct pubkey4io *pk, struct signature4io *sig, uint16_t large_a[LWE_M], uint16_t large_p[LWE_M], unsigned char miu[SHA512_DIGEST_LENGTH]);
//Bob的根据Alice的签名和之前提供的LWE公钥，经过计算决定是否接受Alice的身份及其LWE公钥

#endif // BLISSSIG_H_INCLUDED
