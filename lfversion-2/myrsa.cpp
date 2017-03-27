#include "myrsa.h"
#include <time.h>
#include<stdio.h>
MyRSA::MyRSA()
{
}

MyRSA::~MyRSA()
{
}
/*
 *    以下函数是用来计算信息的散列值
 *
 */
 //MD5
string MyRSA::MD5(const char * message)
{
    string digest;
    Weak::MD5 md5;
    StringSource(message, true,
            new HashFilter(md5, new HexEncoder(new StringSink(digest))));
    return digest;
}
/*
 *输入文件名，返回字符类型的散列值
 */
string MyRSA::MD5File(const char * filename)
{
    string digest;
    Weak::MD5 md5;
    FileSource(filename, true,
            new HashFilter(md5, new HexEncoder(new StringSink(digest))));
    return digest;

}
//SHA512
string MyRSA::Sha512(const char * message)
{
    string digest;
    SHA512 sha;
    StringSource(message, true,
            new HashFilter(sha, new HexEncoder(new StringSink(digest))));
    return digest;
}
/*
 *输入文件名，返回字符类型的散列值
 */
string MyRSA::Sha512File(const char * filename)
{
    string digest;
    SHA512 sha;
    FileSource(filename, true, new HashFilter(sha, new HexEncoder(new StringSink(digest))));
    return digest;
}

/*
 *输入RSA密钥的长度、想要存私钥和公钥的文件名，输出为含公钥的文件和私钥的文件
 */
void MyRSA::GenerateRSAKey(unsigned int keyLength, const char *privFilename,
        const char *pubFilename)
{
    RSAES_OAEP_SHA_Decryptor priv(_rng, keyLength);
    HexEncoder privFile(new FileSink(privFilename));
    priv.DEREncode(privFile);
    privFile.MessageEnd();

    RSAES_OAEP_SHA_Encryptor pub(priv);
    HexEncoder pubFile(new FileSink(pubFilename));
    pub.DEREncode(pubFile);
    pubFile.MessageEnd();
}
/*
    输入秘钥文件的名称，读取秘钥返回字符串类型
*/
string MyRSA::getKey(const char*keyFile)
{
        string key;
        FileSource file(keyFile, true, new StringSink(key));
        return key;
}
/*
 *加密文件，输入公钥、明文文件名、密文文件名，生成密文文件，返回字符串类型的密文
 */
string MyRSA::Encrypt(const char * pubFilename, const char * messageFile,const char* cipherFile)
{
    FileSource pubFile(pubFilename, true, new HexDecoder);
    string message;
    FileSource file(messageFile, true, new StringSink(message));
    RSAES_OAEP_SHA_Encryptor pub(pubFile);
    string result;
    StringSource(message, true,
            new PK_EncryptorFilter(_rng, pub,
                    new HexEncoder(new StringSink(result))));
    FileSink sink(cipherFile);
    sink.Put((byte const*) result.data(), result.size());
    return result;
}
/*
 *解密文件，输入私钥、密文文件名、明文文件名，生成明文文件，返回明文
 */
string MyRSA::Decrypt(const char * privFilename, const char * ciphertextFile,const char* plainFile)
{
    FileSource privFile(privFilename, true, new HexDecoder);
    string ciphertext;
    FileSource file(ciphertextFile, true, new StringSink(ciphertext));
    RSAES_OAEP_SHA_Decryptor priv(privFile);
    string result;
    StringSource(ciphertext, true,
            new HexDecoder(
                    new PK_DecryptorFilter(_rng, priv,
                            new StringSink(result))));

    FileSink sink(plainFile);
    sink.Put((byte const*) result.data(), result.size());
    return result;
}

/*
 *输入私钥的文件、消息的文件和要签名的文件名进行签名
 */
void MyRSA::SignFile(const char * privFilename, const char *messageFilename,
        const char * signatureFilename)
{
    FileSource priFile(privFilename, true, new HexDecoder);
    RSASS<PKCS1v15, SHA>::Signer priv(priFile);
    FileSource f(messageFilename, true,
            new SignerFilter(_rng, priv,
                    new HexEncoder(new FileSink(signatureFilename))));
}

/*
 *输入公钥的文件名、信息的文件名和含有签名的文件确认是否一致，一致返回true否则返回false
 */
bool MyRSA::VerifyFile(const char * pubFilename, const char * messageFilename,
        const char * signatureFilename)
{
    FileSource pubFile(pubFilename, true, new HexDecoder);
    RSASS<PKCS1v15, SHA>::Verifier pub(pubFile);

    FileSource signatureFile(signatureFilename, true, new HexDecoder);
    if (signatureFile.MaxRetrievable() != pub.SignatureLength())
        return false;
    SecByteBlock signature(pub.SignatureLength());
    signatureFile.Get(signature, signature.size());

    VerifierFilter *verifierFilter = new VerifierFilter(pub);
    verifierFilter->Put(signature, pub.SignatureLength());
    FileSource f(messageFilename, true, verifierFilter);

    return verifierFilter->GetLastResult();
}

/*
 *输入私钥的文件名、消息的字符串，返回签名
 */
SecByteBlock MyRSA::SignString(const char * privFilename, const char * message,string HashName)
{
    // calculate the md5(HASH) of the message
    string digest;
    if(HashName=="SHA512"){
         digest = Sha512(message);
    }else{
        digest=MD5(message);
    }
    FileSource priFile(privFilename, true, new HexDecoder);
    RSASSA_PKCS1v15_SHA_Signer priv(priFile);

    // Create signature space
    size_t length = priv.MaxSignatureLength();
    SecByteBlock signature(length);

    // sign message
    priv.SignMessage(_rng, (const byte*) digest.c_str(), digest.length(),
            signature);

    return signature;
}
/*
 *输入公钥的文件名、消息和签名
 */
bool MyRSA::VerifyString(const char * pubFilename, const char * message,
        const SecByteBlock & signature,string HashName)
{
    // calculate the md5 of the message first
   string digest;
    if(HashName=="SHA512"){
         digest = Sha512(message);
    }else{
        digest=MD5(message);
    }
    FileSource pubFile(pubFilename, true, new HexDecoder);
    RSASSA_PKCS1v15_SHA_Verifier verifier(pubFile);

    bool result = verifier.VerifyMessage((const byte*) digest.c_str(),
            digest.length(), signature, signature.size());
    return result;
}


// int main() {

//                 MyRSA rsa;

//                 rsa.GenerateRSAKey(2048, "PriKey", "PubKey");
//                 string message = "testEn";
//                 string ciphertext = rsa.Encrypt("PubKey", message.c_str(),"cipher");
//                 cout << "The cipher is : " << ciphertext << endl;

//                 string decrypted = rsa.Decrypt("PriKey", "cipher","plain");
//                 cout << "The recover is : " << decrypted << endl;


//                 cout << "==============sign file================" << endl;

//                 rsa.SignFile("PriKey", "test","signed");//签名

//                 if (rsa.VerifyFile( "PubKey","test",
//                "signed")) {//验证
//                 cout << "verify correct!" << endl;
//                 } else
//                 cout << "verify error!" << endl;

//                 cout << "============sign string=================" << endl;

//                 string plainText = "Sign me, i am a student from SYSU university!";
//                 SecByteBlock signature = rsa.SignString("PriKey", plainText.c_str(),"SHA512");
//                 cout << "The Signature size is : " << signature.size() << endl;


//                 if (rsa.VerifyString("PubKey", plainText.c_str(),  signature,"SHA512")) {
//                 cout << "Verify correct!" << endl;
//                 } else {
//                 cout << "Verify wrong!" << endl;
//                 }

//                 cout<<"==========================read key========================"<<endl;
//                 cout<<"the pubkey is:"<<rsa.getKey("PubKey");//获取key并显示出来
//                 cout<<"============delete file=================="<<endl;
//                 if(remove("PubKey")==0){//输入需要删除的文件名，进行删除，成功返回0否则返回-1
//                    cout<<"delete success!"<<endl;
//                 }else{
//                    cerr<<"delete fail"<<endl;
//                 }
//                 return 0;
// }
