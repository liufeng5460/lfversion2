#ifndef __ENTROPY_H
#define __ENTROPY_H
#include <fstream>
#include <stdint.h>

#define ENTROPYPOOL_SIZE 10 // *512 bits

class Entropy {
	private:
		unsigned long entropyBitPool;
		unsigned char* entropyCharPool;
		uint32_t* entropyUint32Pool;
		unsigned long* entropyLongPool;
		long posEntropyBitPool;
		long posEntropyCharPool;
		long posEntropyUint32Pool;
		long posEntropyLongPool;

		unsigned char* current_seed;

		FILE* fp;

	public:
		Entropy();
		~Entropy();

		void sha512(unsigned char* hash);
		void populateCharPool();
		void populateUint32Pool();
		void populateLongPool();
		void populateBitPool();
		bool getRandomBit();
		unsigned char getRandomChar();
		uint32_t getRandomUint32();
		unsigned long getRandomLong();
		unsigned char getURandomChar();
		unsigned long getURandomLong();
};

#endif
