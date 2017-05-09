
#ifndef __SIGN_H
#define __SIGN_H

#include "Parameters.h"
#include "Fft.h"
#include "Setup.h"
#include "KeyGen.h"
#include "Sampler.h"
#include <string>
#include <openssl/sha.h>

#define LWE_M 512

struct signature {
	long* z1;
	long* z2;
	long* z1High;
	long* z1Low;
	long* z2Carry;
	long* indicesC;
};

struct signature4io {
    long z1[BlissN];
    long z2[BlissN];
    long z1High[BlissN];
    long z1Low[BlissN];
    long z2Carry[BlissN];
    long indicesC[kappa];
};

class Sign {
	private:
		Sampler* sampler;
		Entropy* random;
		long bound_NkS;

	public:
		struct signature signOutput;
		Sign(Setup setup, Sampler* s, Entropy* randomGen);
		long signMessage(const struct pubkey& pk, const struct seckey& sk, const std::string message);
		long signHash(const struct pubkey& pk, const struct seckey& sk, unsigned char hash[SHA512_DIGEST_LENGTH]);
		void mult_by_c(long* result, unsigned char* ls, bool isG, long offset, long* indices);
		void mult_by_a2_fft(long* ay, long* a_fft, long* y2);
		void computeCarries(long* result, long* ay, long* z2);
		void generateC(long* indices, long* ay, char* hash);
		~Sign();
};

void mysha512(unsigned char* hash, char* message, long size);
void roundD(long* result, long* v);
unsigned long norm2(long* a);
long scalProd(long* z, long* a);

#endif
