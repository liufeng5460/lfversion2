#include "maininterface.h"
#include <QApplication>
#include <QDir>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainInterface w;
    w.show();

    QDir *dirHandler=new QDir();
    bool exist;

    // 获取程序执行时的工作目录
    QString currentDir=QCoreApplication::applicationDirPath();

    // 如果 不存在 Key 子目录，就创建它
    exist = dirHandler->exists(currentDir+"/Key");
    if(!exist) dirHandler->mkdir(currentDir+"/Key");

    // 如果 不存在 Tmp 子目录，就创建它
    exist = dirHandler->exists(currentDir+"/Tmp");
    if(!exist) dirHandler->mkdir(currentDir+"/Tmp");

    // 如果 不存在 Key/AES 子目录，就创建它
    exist = dirHandler->exists(currentDir+"/Key/AES");
    if(!exist) dirHandler->mkdir(currentDir+"/Key/AES");

    // 如果 不存在 Key/RSA 子目录，就创建它
    exist = dirHandler->exists(currentDir+"/Key/RSA");
    if(!exist) dirHandler->mkdir(currentDir+"/Key/RSA");


//    qDebug()<<QCoreApplication::applicationDirPath();
   // QCoreApplication::addLibraryPath("./lib");
    //qDebug()<<QCoreApplication::libraryPaths();


    return a.exec();
}
