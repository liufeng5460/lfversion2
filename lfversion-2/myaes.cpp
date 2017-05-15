#include "myaes.h"
#include <time.h>
#include <unistd.h>
MyAES::MyAES()
{
}

MyAES::~MyAES()
{

}

void MyAES::setKey(string key,string iv){
    this->Key=key;
    this->Iv=iv;
}

void MyAES::getKey()
{
   cout<<"key is:"<<Key<<endl;
   cout<<"Iv is"<<Iv<<endl;
}

void MyAES::getKey(string& key, string& iv)
{
    key = this->Key;
    iv = this->Iv;
}

bool MyAES::GenerateKey(int length)
{
    if(length!=16 && length!=24 && length!=32){
        cerr<<"输入秘钥长度有误，只有16、24、 32三种";
        return false;
    }else{
            AutoSeededRandomPool rnd;
            byte key1[length];
            rnd.GenerateBlock(key1, length);
            // Generate a random IV
            byte iv1[length];
            rnd.GenerateBlock(iv1, length);

            HexEncoder encoder;
            encoder.Attach( new StringSink( Key ) );

            encoder.Put( key1, sizeof(key1 ) );
            encoder.MessageEnd();

            HexEncoder encoder1;
            encoder1.Attach( new StringSink( Iv ) );

            encoder1.Put( iv1, sizeof(iv1 ) );
            encoder1.MessageEnd();
            return true;
    }

}

/*
加密字符串，返回密文
 */
string MyAES::Encrypt(const string &plainText)
{
    string cipher,key, iv;
    StringSource ssk(this->Key,
                     true,
                     new HexDecoder(new StringSink(key)));

    StringSource ssv(this->Iv,
                     true,
                     new HexDecoder( new StringSink(iv)));
    CBC_Mode<AES>::Encryption aesEncryptor;

    aesEncryptor.SetKeyWithIV((byte const*) key.data(), key.size(), (byte const*) iv.data());

    StringSource(plainText, true,
            new StreamTransformationFilter(aesEncryptor,
                    new StringSink(cipher)));
    return cipher;
}

/*
解密字符串，返回解密后明文
 */
string MyAES::Decrypt(const string & cipher)
{
    string recover,key, iv;
    StringSource ssk(Key, true /*pumpAll*/,
    new HexDecoder(
        new StringSink(key)
    ) // HexDecoder
); // StringSource

    StringSource ssv(Iv, true /*pumpAll*/,
        new HexDecoder(
            new StringSink(iv)
        ) // HexDecoder
    ); // StringSource

    CBC_Mode<AES>::Decryption aesDecryptor;
    aesDecryptor.SetKeyWithIV((byte const*) key.data(), key.size(), (byte const*) iv.data());

    StringSource(cipher, true,
            new StreamTransformationFilter(aesDecryptor,
                    new StringSink(recover)));
    return recover;
}

//加密文件，输入需要加密文件的文件名和加密后文件的文件名
bool MyAES::EncryptFile(const string & inFilename, const string & outFilename)
{
    // check if the file 'inFilename' exists.
    if (access(inFilename.c_str(), 0) == -1)
    {
        cout << "The file " << inFilename << " is not exist! " << endl;
        return false;
    }
    // file exists, the encrypt the file
     string key, iv;
    StringSource ssk(Key, true /*pumpAll*/,
    new HexDecoder(
        new StringSink(key)
    ) // HexDecoder
); // StringSource

    StringSource ssv(Iv, true /*pumpAll*/,
        new HexDecoder(
            new StringSink(iv)
        ) // HexDecoder
    ); // StringSource
    CBC_Mode<AES>::Encryption aesEncryptor;

    aesEncryptor.SetKeyWithIV((byte const*) key.data(), key.size(), (byte const*) iv.data());

    FileSource(inFilename.c_str(), true,
            new StreamTransformationFilter(aesEncryptor,
                    new FileSink(outFilename.c_str())));

    return true;
}

//解密文件，输入需要解密的文件名和解密后的文件名
bool MyAES::DecryptFile(const string & decFilename,
        const string & recoverFilename)
{
    // check if the file 'decFilename' exists!
    if (access(decFilename.c_str(), 0) == -1)
    {
        cout << "The file " << decFilename << " is not exist! " << endl;
        return false;
    }
    // exist , then decrypt the file
     string key, iv;
    StringSource ssk(Key, true /*pumpAll*/,
    new HexDecoder(
        new StringSink(key)
    ) // HexDecoder
); // StringSource

    StringSource ssv(Iv, true /*pumpAll*/,
        new HexDecoder(
            new StringSink(iv)
        ) // HexDecoder
    ); // StringSource

    CBC_Mode<AES>::Decryption aesDecryptor;
    aesDecryptor.SetKeyWithIV((byte const*) key.data(), key.size(), (byte const*) iv.data());
    FileSource(decFilename.c_str(), true,
            new StreamTransformationFilter(aesDecryptor,
                    new FileSink(recoverFilename.c_str())));
    return true;
}
//从本地导入秘钥，输入秘钥所在位置及文件名
void MyAES::LoadKey(const char * KeyFilename){
    string str;
    FileSource file(KeyFilename, true, new StringSink(str));

    setKey(str.substr(0,str.size()/2),str.substr(str.size()/2,str.size()));
}
//保存秘钥，输入保存秘钥的名称（包含位置，绝对路径）
void MyAES::SaveKey(const char * KeyFilename){
    FileSink sink(KeyFilename);
    sink.Put((byte const*) Key.data(), Key.size());
    sink.Put((byte const*) Iv.data(), Iv.size());
}
// int main() {

//     MyAES aes;
//     aes.GenerateKey(16);//生成16 byte AES秘钥
//     aes.SaveKey("key.txt");
//     aes.LoadKey("key.txt");
//     string plainText = "Hello World!";

//     string cipher = aes.Encrypt(plainText);
//     cout << "The cipher is : " << cipher << endl;

//     string recover = aes.Decrypt(cipher);
//     cout << "The recover is : " << recover << endl;

//     cout << "=====================" << endl;
//       // 加解密文件，既可以使用相对路径也可以绝对路径
//     string inFilename = "Test";//用于测试的文件，此处使用相对路径，绝对路径也可以
//     string outFilename = "aesEncrypt";
//     string recoverFilename = "aesRecover";

//     if(aes.EncryptFile(inFilename, outFilename)){
//     cout << "*__*" << endl << "Encrypt succeed!" << endl;
//     if(aes.DecryptFile(outFilename, recoverFilename)){
//     cout << "*__*" << endl << "Recover succeed!" << endl;
//     } else
//     cout << ")__(" << endl << "Recover failed!" << endl;
//     } else
//     cout << ")__(" << endl << "Encrypt failed!" << endl;
//     return 0;
// }
