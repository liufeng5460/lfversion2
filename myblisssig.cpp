#include "myblisssig.h"
#include "status.h"

#include <QFile>
#include <QTextStream>

MyBlissSig::MyBlissSig()
{

}

void MyBlissSig::generateKey()
{
    BlissKeyGen(&pk,&sk);
}

void MyBlissSig::save(const QString &pkFileName, const QString &skFileName)
{
    QFile pkFile(Status::LWEDir+pkFileName);
    QTextStream out;
    if(pkFile.open(QIODevice::WriteOnly |QIODevice::Text)){
        out.setDevice(&pkFile);

        // write data start
        for(int i=0; i<2*N-1; i++)
        {
            out<<pk.a1[i];
        }
        out<<pk.a2<<pk.offset<<pk.modulus;
        for(int i=0; i<N; i++)
        {
            out<<pk.a_fft[i];
        }
        // write data end

        pkFile.close();
    }else{
        qDebug()<<"can not open "<<pkFile.fileName();
    }


    QFile skFile(Status::LWEDir+skFileName);

    if(skFile.open(QIODevice::WriteOnly|QIODevice::Text)){
        out.setDevice(&skFile);

        // write data start

        for(int i=0; i<N; i++)
        {
            out<<sk.s1[i]<<sk.s2[i];
        }
        for(int i=0; i<2*N-1; i++)
        {
            out<<sk.ls1[i]<<sk.ls2[i];
        }
        out<<offset;

        // write end

        skFile.close();
    }else{
         qDebug()<<"can not open "<<skFile.fileName();
    }
}


void MyBlissSig::load(const QString &pkFileName, const QString &skFileName)
{

}

void MyBlissSig::decrypt(QByteArray &cipher, QByteArray &message)
{

}

void MyBlissSig::encrypt(const QByteArray &message, QByteArray &cipher)
{

}

void MyBlissSig::encryptFile(const QString &messageFileName, const QString &cipherFileName)
{

}

void MyBlissSig::decryptFile(const QString &messageFileName, const QString &cipherFileName)
{

}
