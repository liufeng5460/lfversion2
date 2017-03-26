#include "mainwindow.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //检查文件夹是否存在，不存在则创建
    QDir *checkDir=new QDir();
    bool exist;
    QString dir=QApplication::applicationDirPath();
    exist = checkDir->exists(dir+"/Key");
    if(!exist) checkDir->mkdir(dir+"/Key");
    exist = checkDir->exists(dir+"/Tmp");
    if(!exist) checkDir->mkdir(dir+"/Tmp");
    exist = checkDir->exists(dir+"/Key/AES");
    if(!exist) checkDir->mkdir(dir+"/Key/AES");
    exist = checkDir->exists(dir+"/Key/RSA");
    if(!exist) checkDir->mkdir(dir+"/Key/RSA");

    return a.exec();
}
