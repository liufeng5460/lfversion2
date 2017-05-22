#ifndef MYBLISS_H
#define MYBLISS_H

#include <Bliss.h>
#include <QString>



class MyBliss
{
public:
    MyBliss();
    ~MyBliss();

    void generateKey();
    void save(const QString& pkFileName, const QString& skFileName);
    void load(const QString& pkFileName, const QString& skFileName);
    signature4io*  sign(QString message);
    bool verify(QString message,signature4io* sig );
    QString pkToString();
    QString skToString();

    static pubkey4io* getPubkey(const QString& filePath, bool byCerti = false);
    static seckey4io* getSeckey(const QString& filePath);

    static bool sigFile(const QString& certiName,const QString& srcFilePath, const QString& dstFilePath);
    static bool verifyFile(const QString& certiName, const QString& srcFilePath, const QString& sigFilePath);

    static QString sigToString(signature4io* sig);
    static signature4io* getSigFromString(const QString& sigString);
    pubkey4io* pk;
    seckey4io* sk;

};

#endif // MYBLISS_H
