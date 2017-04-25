#ifndef BLISSSIG_H_INCLUDED
#define BLISSSIG_H_INCLUDED

#include "KeyGen.h"
#include "Sign.h"

void BlissKeyGen(struct pubkey4io *pk, struct seckey4io *sk);

void BlissSigM(struct pubkey4io *pk, struct seckey4io *sk, struct signature4io *sig, const std::string message);
bool BlissVerifyM(struct pubkey4io *pk, struct signature4io *sig, const std::string message);

void BlissSigF(struct pubkey4io *pk, struct seckey4io *sk, struct signature4io *sig, const std::string filename);
bool BlissVerifyF(struct pubkey4io *pk, struct signature4io *sig, const std::string filename);

#endif // BLISSSIG_H_INCLUDED
