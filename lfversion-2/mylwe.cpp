#include "mylwe.h"
#include "status.h"
#include <QDebug>
#include <iostream>
#include <QMessageBox>
#include <QFile>
MyLWE::MyLWE()
{
    pk1 = new uint16_t[LWE_M];
    pk2 = new uint16_t[LWE_M];
    sk = new uint16_t[LWE_M];
}

MyLWE::~MyLWE()
{
    delete[] pk1;
    delete[] pk2;
    delete[] sk;
}

void MyLWE::generateKey()
{
    LWEKeyGen(pk1,pk2,sk);
//    auto test = [&]{
//        for(int i=0; i<LWE_M; i++){
//            qDebug()<<sk[i];
//        }
//    };
    //test();
}

void MyLWE::save(const QString & pkFileName, const QString & skFileName)
{
    QFile pkFile(Status::LWEDir+pkFileName);
    QTextStream out;
    if(pkFile.open(QIODevice::WriteOnly |QIODevice::Text)){
        out.setDevice(&pkFile);
        for(int i=0; i<LWE_M; i++)
        {
            out<<pk1[i]<<" ";
            out<<pk2[i]<<"\n";
        }
        pkFile.close();
    }else{
        qDebug()<<"can not open "<<pkFile.fileName();
    }


    QFile skFile(Status::LWEDir+skFileName);

    if(skFile.open(QIODevice::WriteOnly|QIODevice::Text)){
        out.setDevice(&skFile);
        for(int i=0; i<LWE_M; i++)
        {
            out<<sk[i]<<"\n";
        }
        skFile.close();
    }else{
         qDebug()<<"can not open "<<skFile.fileName();
    }
}

void MyLWE::load(const QString &pkFileName, const QString &skFileName)
{
   QFile pkFile(Status::LWEDir+pkFileName);
   QTextStream in;
   if(pkFile.open(QIODevice::ReadOnly |QIODevice::Text))
   {
        in.setDevice(&pkFile);
        QStringList pairs;
        for(int i=0; i<LWE_M; i++)
        {
            pairs = in.readLine().split(" ");
            pk1[i] = pairs.at(0).toUShort();
            pk2[i] = pairs.at(1).toUShort();
        }
        pkFile.close();

   }
   else
   {
       qDebug()<<"Can not open "<<pkFile.fileName()<<" in MyLWE::load function!";
   }

   QFile skFile(Status::LWEDir+skFileName);
   if(skFile.open(QIODevice::ReadOnly |QIODevice::Text))
   {
       in.setDevice(&skFile);
        for(int i=0; i<LWE_M; i++)
        {
            sk[i] = in.readLine().toUShort();
        }
        skFile.close();
   }
   else
   {
       qDebug()<<"Can not open "<<skFile.fileName()<<" in MyLWE::load function!";
   }


   auto test = [&]{
        for(int i=0; i<LWE_M; i++)
        {
            qDebug()<<pk2[i];
        }
   };
   // test();

}
void MyLWE::encrypt(const QByteArray &message, QByteArray &cipher)
{
    encryptMessage(pk1,pk2,message,cipher);
}


void MyLWE::encryptMessage(uint16_t*pk1, uint16_t* pk2,const QByteArray& message, QByteArray& cipher)
{
    if(message.size() > 64)
    {
        QMessageBox::information(Status::mainWindow
                                 ,"LWE Encrytion"
                                 ,"The bytes number of message can not exceed 64");
    }

    auto charToArray = [](char c,uint16_t *result)
    {
        for(int i=0; i<8; i++)
        {
            result[i] = c&1;
            c>>=1;
        }

    };
    LWE_t m;
    int k=0;
    uint16_t* result = new uint16_t[8];
    int i=0;
    for(; i<message.size(); i++)
    {
        char c = message.at(i);

        charToArray(c,result);
        for(int j=0; j<8;j++)
        {
            m[k++] =result[j];
        }
    }
    delete[]  result;
    for(; i<LWE_M; i++)
    {
        m[k++]=0;
    }
    LWE_t c1,c2;
    LWEEnc(pk1,pk2,m,c1,c2);
    QDataStream out(&cipher,QIODevice::WriteOnly);
    for(int i=0; i<LWE_M; i++)
    {
        out<<c1[i]<<c2[i];
    }
}

void MyLWE::decrypt(QByteArray &message, QByteArray &cipher)
{
    QDataStream in(cipher);
    LWE_t c1,c2;
    for(int i=0;i<LWE_M; i++)
    {
        in>>c1[i]>>c2[i];
    }
    LWE_t m;
    LWEDec(sk,c1,c2,m);
    auto setBit = [](char& c,int i,int value)
    {
        if(value == 1)
        {
            int mask = 1;
            mask <<= i;
            c |= mask;
        }
        if(value == 0)
        {
            int mask[] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};
            c &= mask[i];
        }
    };
    char tmp[64];
    int k=0;
    for(int i=0; i<64; i++)
    {
        for(int j=0; j<8;j++)
        {
            setBit(tmp[i],j,m[k++]);
        }
    }
    cipher = QByteArray(tmp);
//    qDebug()<<"message length in LWE::Encrypt: "+cipher.length();

}

void MyLWE::encryptFile(const QString &messageFileName, const QString &cipherFileName)
{
    QFile messageFile(messageFileName);
    QFile cipherFile(cipherFileName);
    messageFile.open(QIODevice::ReadOnly);
    cipherFile.open(QIODevice::WriteOnly);
    auto message = messageFile.readAll();
    QByteArray cipher;
    encrypt(message, cipher);
    cipherFile.write(cipher);
    messageFile.close();
    cipherFile.close();
}

void MyLWE::decryptFile(const QString &messageFileName, const QString &cipherFileName)
{

    QFile cipherFile(cipherFileName);
    cipherFile.open(QIODevice::ReadOnly);
    auto cipher = cipherFile.readAll();
    QByteArray message;
    decrypt(cipher,message);
    QFile messageFile(messageFileName);
    messageFile.open(QIODevice::WriteOnly);
    messageFile.write(message);
    messageFile.close();
    cipherFile.close();
}
