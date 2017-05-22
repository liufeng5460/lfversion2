#ifndef MYRSA_H_
#define MYRSA_H_

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <iostream>
#include <string>

#include <cryptopp/rsa.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/md5.h>
#include<cryptopp/sha.h>

using namespace std;
using namespace CryptoPP;

class MyRSA
{
public:
    MyRSA();
    ~MyRSA();

    static string MD5(const char * message);
    static string MD5File(const char * filename);

    static string Sha512(const char* message);//SHA1、SHA256、SHA224、SHA512、SHA384都可以使用，此处使用的是SHA512
    static string Sha512File(const char* filename);

    void GenerateRSAKey(unsigned int keyLength, const char *privFilename,
            const char *pubFilename);//输入公私钥的文件名和长度，自动生成公私钥
    string getKey(const char*keyFile);//输入秘钥的文件名，返回秘钥的内容

    string Encrypt(const char * pubFilename, const char * messageFile,const char* cipherFile);//加密文件，输入公钥、明文文件名、密文文件名，生成密文文件，返回字符串类型的密文
    string Decrypt(const char * privFilename, const char * ciphertextFile,const char* plainFile);//解密文件，输入私钥、密文文件名、明文文件名，生成明文文件，返回明文

    void SignFile(const char * privFilename, const char * messageFilename,
            const char * signatureFilename);
    bool VerifyFile(const char *pubFilename, const char * messageFilename,
            const char * signatureFilename);

    SecByteBlock SignString(const char *privFilename, const char * message,string HashName);
    bool VerifyString(const char * pubFilename, const char * messsage,
            const SecByteBlock &SecByteBlock,string HashName);
private:
    AutoSeededRandomPool _rng;
};

#endif /* MYRSA_H_ */
