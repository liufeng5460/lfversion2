#ifndef MYLWE_H
#define MYLWE_H

#include <LWEEnc.h>
#include <QString>
using LWE_t =  uint16_t [LWE_M];

class MyLWE
{
public:
    MyLWE();
    ~MyLWE();
    void generateKey();
    void save(const QString& pkFileName, const QString& skFileName);
    void load(const QString& pkFileName, const QString& skFileName);
    void encrypt(const QByteArray& message,QByteArray& cipher);
    void decrypt(QByteArray& cipher,QByteArray& message);

private:

    uint16_t *pk1,*pk2,*sk;
};

#endif // MYLWE_H
