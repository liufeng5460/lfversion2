#ifndef MYAES_H_
#define MYAES_H_

#include <cryptopp/aes.h>
#include <cryptopp/default.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>
#include<crypto++/hex.h>
#include <crypto++/base64.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace CryptoPP;
using namespace std;

class MyAES
{
private:
    string Key;
    string Iv;//轮秘钥常量
public:
    MyAES();

    ~MyAES();

    void setKey(string key,string iv);
    void getKey();//用于测试

    //使用密钥加密明文返回密文
    string Encrypt(const string &plainText);

    //使用相同的密钥解密
    string Decrypt(const string &cipher);
    //加密文件
   bool EncryptFile(const string & inFilename, const string & outFilename);
    //解密文件
    bool DecryptFile(const string & DecFilename,const string & recoverFilename);
    //没有秘钥时生成秘钥
    bool GenerateKey(int length);//16、32
    //从指定文件中导入秘钥
    void LoadKey(const char *KeyFilename);
    //存储秘钥到指定文件
    void SaveKey(const char * KeyFilename);
};

#endif /* MYAES_H_ */
