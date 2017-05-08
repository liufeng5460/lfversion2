#ifndef MYBLISSSIG_H
#define MYBLISSSIG_H

#include "BlissSig.h"

#include <QString>
#include <QByteArray>


class MyBlissSig
{
public:
    MyBlissSig();
    void generateKey();
    void save(const QString& pkFileName, const QString& skFileName);
    void load(const QString& pkFileName, const QString& skFileName);
    void encrypt(const QByteArray& message,QByteArray& cipher);
    void encryptFile(const QString& messageFileName, const QString& cipherFileName);
    void decryptFile(const QString& messageFileName, const QString& cipherFileName);
    void decrypt(QByteArray& cipher,QByteArray& message);


    pubkey4io pk;
    seckey4io sk;
};

#endif // MYBLISSSIG_H
