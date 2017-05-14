#include "mybliss.h"
#include "status.h"
#include <QTextStream>
#include <QByteArray>
#include <QFile>
#include <QDebug>

MyBliss::MyBliss()
{
    pk = new pubkey4io;
    sk = new seckey4io;
}

MyBliss::~MyBliss()
{
    delete pk;
    delete sk;
}

void MyBliss::generateKey()
{
    BlissKeyGen(pk,sk);
}


QString MyBliss::pkToString()
{
    if(pk==nullptr) return QString("");
    QByteArray result;
    QTextStream out(&result, QIODevice::WriteOnly);

//       for    long a1[2*BlissN-1];
    for(int i=0; i<2*BlissN-1; i++)
    {
        out<<pk->a1[i]<<" ";
    }
    out<<"\n";

//       for    long a2;
    out<<pk->a2<<"\n";

//       long offset;
    out<<pk->offset<<"\n";

//       long modulus;
    out<<pk->modulus<<"\n";

//       long a_fft[BlissN];
    for(int i=0; i<BlissN; i++)
    {
        out<<pk->a_fft[i]<<" ";
    }
    out<<"\n";

    out.flush();
    return QString(result);



}

QString MyBliss::skToString()
{
    if(sk==nullptr) return QString("");
    QByteArray result;
    QTextStream out(&result, QIODevice::WriteOnly);

//    for long s1[BlissN];
    for(int i=0;i<BlissN; i++)
    {
        out<<sk->s1[i]<<" ";
    }
    out<<"\n";

//       long s2[BlissN];
    for(int i=0; i<BlissN; i++)
    {
        out<<sk->s2[i]<<" ";
    }
    out<<"\n";

//       unsigned char ls1[2*BlissN-1];
    for(int i=0; i<2*BlissN-1; i++)
    {
        out<<sk->ls1[i]<<" ";
    }
    out<<"\n";

//       unsigned char ls2[2*BlissN-1];
    for(int i=0; i<2*BlissN-1; i++)
    {
        out<<sk->ls2[i]<<" ";
    }
    out<<"\n";

//       long offset;
    out<<sk->offset;
    out<<"\n";

    out.flush();
    return QString(result);

}

void MyBliss::save(const QString &pkFileName, const QString &skFileName)
{
    QFile pkFile(Status::BlissDir+pkFileName);
    pkFile.open(QIODevice::WriteOnly);
    QTextStream out(&pkFile);
    out<<pkToString();
    pkFile.close();


    QFile skFile(Status::BlissDir+skFileName);
    skFile.open(QIODevice::WriteOnly);
    out.setDevice(&skFile);
    out<<skToString();
    skFile.close();


}

void MyBliss::load(const QString& pkFileName, const QString& skFileName)
{
    pk = getPubkey(Status::BlissDir+pkFileName);
    sk = getSeckey(Status::BlissDir+skFileName);
}

signature4io* MyBliss::sign(QString message)
{
    signature4io* sig = new signature4io;
    BlissSigM(pk,sk,sig,message.toStdString());
    //qDebug()<<"MyBliss::sign exit";
    return sig;
}

bool MyBliss::verify(QString message, signature4io* sig)
{
    if(sig==nullptr)
    {
        qDebug()<<"In MyBliss::verify the sig = nullptr";
    }
    return BlissVerifyM(pk,sig,message.toStdString());
}

pubkey4io* MyBliss::getPubkey(const QString &filePath, bool byCerti)
{
    pubkey4io* pk = new pubkey4io;

    QFile certiFile(filePath);
    certiFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream fin(&certiFile);
    if(byCerti)
    {
        fin.readLine();
    }

    //       for    long a1[2*BlissN-1];
        for(int i=0; i<2*BlissN-1; i++)
        {
            fin>>pk->a1[i];
        }


    //       for    long a2;
        fin>>pk->a2;

    //       long offset;
        fin>>pk->offset;

    //       long modulus;
        fin>>pk->modulus;

    //       long a_fft[BlissN];
        for(int i=0; i<BlissN; i++)
        {
            fin>>pk->a_fft[i];
        }

    certiFile.close();
    return pk;
}

seckey4io* MyBliss::getSeckey(const QString &filePath)
{
    seckey4io* sk = new seckey4io;

    QFile skFile(filePath);
    skFile.open(QIODevice::ReadOnly| QIODevice::Text);
    QTextStream in(&skFile);

    //    for long s1[BlissN];
        for(int i=0;i<BlissN; i++)
        {
            in>>sk->s1[i];
        }

    //       long s2[BlissN];
        for(int i=0; i<BlissN; i++)
        {
            in>>sk->s2[i];
        }


    //       unsigned char ls1[2*BlissN-1];
        unsigned int temp;
        for(int i=0; i<2*BlissN-1; i++)
        {
            in>>temp;
            sk->ls1[i] = static_cast<unsigned char>(temp);
        }

    //       unsigned char ls2[2*BlissN-1];
        for(int i=0; i<2*BlissN-1; i++)
        {
            in>>temp;
            sk->ls2[i] = static_cast<unsigned char>(temp);
        }

    //       long offset;
        in>>sk->offset;

     skFile.close();
     return sk;
}
