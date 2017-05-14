#include "mainwindow.h"
#include "netaction.h"
#include "status.h"
#include "mybliss.h"
#include "mylwe.h"


//#include "netserver.h"
#include <QApplication>
#include <QDir>
#include <iostream>
#include <QDebug>
#include <cstdint>
#include <LWEEnc.h>
//#include <BlissSig.h>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Status::init();
    MainWindow w;
    w.show();

    auto test = []{
        QString message = "经过计算决定是否";
        MyLWE lwe;
        lwe.generateKey();
        QByteArray cipherArray;
        MyLWE::encryptMessage(lwe.pk1,lwe.pk2,message.toUtf8(),cipherArray);
        QByteArray plainArray;
        lwe.decrypt(plainArray, cipherArray);
        qDebug()<<QString(cipherArray);
    };
    test();

    return a.exec();
}






