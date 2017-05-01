#include <iostream>
#include <fstream>
#include <cstring>
#include <openssl/sha.h>
#include "Setup.h"
#include "KeyGen.h"
#include "Sampler.h"
#include "Sign.h"
#include "Verify.h"
#include "Entropy.h"
#include "NTL/ZZ_pE.h"
#include "BlissAuth.h"

/*
	Sha-512 of message into hash
*/
void sha512(unsigned char* hash, char* message, long size)
{
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, message, size);
    SHA512_Final(hash, &sha512);
}


void BlissKeyGen(struct pubkey4io *pk, struct seckey4io *sk)
{

    Setup setup;
    Entropy random;
    Sampler sampler(sigma, alpha_rejection, &random);
    KeyGen key(setup, &random);

    memcpy((*pk).a1,key.pk.a1,(2*N-1)*sizeof(long));
    (*pk).a2=key.pk.a2;
    (*pk).offset=key.pk.offset;
    (*pk).modulus=key.pk.modulus;
    memcpy((*pk).a_fft,key.pk.a_fft,N*sizeof(long));

    long i;
    for(i=0;i<N;i++) (*sk).s1[i] = NTL::to_long(NTL::coeff(key.sk.s1, i)) ;
    for(i=0;i<N;i++) (*sk).s2[i] = NTL::to_long(NTL::coeff(key.sk.s2, i));
    memcpy((*sk).ls1,key.sk.ls1,(2*N-1));
    memcpy((*sk).ls2,key.sk.ls2,(2*N-1));
    (*sk).offset=key.sk.offset;
}

void Commitment(struct pubkey4io *pk, long u[N])
{
    // Define temporary variables
	long i;
	long* y1; y1 = new long[N];
	long* y2; y2 = new long[N];

	/* Setup */
    Setup setup;
	Entropy random;
	Sampler sampler(sigma, alpha_rejection, &random);

    for (i=0; i<N; i++) {
		y1[i] = sampler.SamplerGaussian();
		u[i] = y1[i]*W[i]; // Formatting for FFT
		y2[i] = sampler.SamplerGaussian();
	}

	/* Sign */
	Sign sign(setup, &sampler, &random);
	// Compute a/(q+2)*y_1 + y_2
	sign.mult_by_a2_fft(u, (*pk).a_fft, y2);
}

void Challenge(unsigned char miu[SHA512_DIGEST_LENGTH])
{
    /* Setup */
	Entropy random;

	for(long i=0; i<SHA512_DIGEST_LENGTH; i++)
		miu[i]=random.getRandomChar();
}

long Answer(struct pubkey4io *pk, struct seckey4io *sk, struct signature4io *sig, long u[N], unsigned char miu[SHA512_DIGEST_LENGTH])
{
    pubkey publickey;
    seckey secretkey;

	publickey.a1 = (*pk).a1;
    publickey.a2 = (*pk).a2;
    publickey.offset = (*pk).offset;
    publickey.modulus = (*pk).modulus;
    publickey.a_fft = (*pk).a_fft;

    long k;
    NTL::clear(secretkey.s1);
    for(k=0;k<N;k++) NTL::SetCoeff(secretkey.s1, k, (*sk).s1[k]);
    NTL::clear(secretkey.s2);
    for(k=0;k<N;k++) NTL::SetCoeff(secretkey.s2, k, (*sk).s2[k]);
    secretkey.ls1 = (*sk).ls1;
    secretkey.ls2 = (*sk).ls2;
    secretkey.offset= (*sk).offset;

    /* Setup */
    Setup setup;
	Entropy random;
	Sampler sampler(sigma, alpha_rejection, &random);
	/* Sign */
	Sign sign(setup, &sampler, &random);
	long nb_tests;
	nb_tests = sign.signHash(publickey, secretkey, u, miu);

    memcpy((*sig).z1,sign.signOutput.z1,N*sizeof(long));
    memcpy((*sig).z2,sign.signOutput.z2,N*sizeof(long));
    memcpy((*sig).z1High,sign.signOutput.z1High,N*sizeof(long));
    memcpy((*sig).z1Low,sign.signOutput.z1Low,N*sizeof(long));
    memcpy((*sig).z2Carry,sign.signOutput.z2Carry,N*sizeof(long));
    memcpy((*sig).indicesC,sign.signOutput.indicesC,kappa*sizeof(long));

    return nb_tests;
}

bool Decision(struct pubkey4io *pk, struct signature4io *sig, long u[N], unsigned char miu[SHA512_DIGEST_LENGTH], long nb_tests)
{
    pubkey publickey;

	publickey.a1 = (*pk).a1;
    publickey.a2 = (*pk).a2;
    publickey.offset = (*pk).offset;
    publickey.modulus = (*pk).modulus;
    publickey.a_fft = (*pk).a_fft;

	/* Setup */
    Setup setup;
	Entropy random;
	Sampler sampler(sigma, alpha_rejection, &random);
	signature ssig;

	ssig.z1 = (*sig).z1;
    ssig.z2 = (*sig).z2;
    ssig.z1Low = (*sig).z1Low;
    ssig.z1High = (*sig).z1High;
    ssig.z2Carry = (*sig).z2Carry;
    ssig.indicesC = (*sig).indicesC;

    long i, j;
    char old_miu[SHA512_DIGEST_LENGTH];
    for(i=0; i<nb_tests; i++) {
        for (j=0; j<SHA512_DIGEST_LENGTH; j++) old_miu[j] = miu[j];
        sha512(miu, old_miu, SHA512_DIGEST_LENGTH);
    }

	/* Verify */
	Verify verify;
	bool valid = verify.verifyHash(publickey, ssig, miu);
	if(valid)
        return 1;
    else
        return 0;

}

