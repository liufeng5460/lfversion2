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

    auto startServer = []{
       NetAction* server = new NetAction;
    };
    startServer();

    /*
    auto LWETest = []{
        MyLWE lwe;
        lwe.load("test2.lwe.pub","test2.lwe.pri");
        QByteArray cipher;
        lwe.encrypt(QByteArray("123"),cipher);
        qDebug()<<"cipher after encrypt length: "<<cipher.length();
        QByteArray message;
        lwe.decrypt(cipher,message);
          qDebug()<<"message after decrypt length: "<<message.length();
        qDebug()<<"message: "+QString(message);
        qDebug()<<QString(message.toHex());
    };
    LWETest();
    */


    auto BlissTest= []{
        MyBliss bliss;
        bliss.generateKey();
       // bliss.save("bliss","sbliss");
        QString message = "nihao";
        auto sig = bliss.sign(message);
        //sig->indicesC[0]=3;
        qDebug()<<"verified: "<<bliss.verify(message,sig);

        delete sig;
        qDebug()<<"BlissTest exit";
    };
   // BlissTest();
    return a.exec();
}






