#ifndef MYBLISS_H
#define MYBLISS_H

#include<Bliss.h>
#include<QString>

class MyBliss
{
public:
    MyBliss();
    ~MyBliss();

    void generateKey();
    void fromString(QString& pkString, QString& skString);
    void save(const QString& pkFileName, const QString& skFileName);
    void load(const QString& pkFileName, const QString& skFileName);
    signature4io*  sign(QString message);
    bool verify(QString message,signature4io* sig );
    QString pkToString();
    QString skToString();
    static pubkey4io* getPubkey(const QString& filePath);



    pubkey4io* pk;
    seckey4io* sk;

};

#endif // MYBLISS_H
