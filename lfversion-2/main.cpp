#include "mainwindow.h"
//#include "netserver.h"
#include <QApplication>
#include <QDir>
void createDirs();
void netSetup(quint16 port, QWidget* ctx);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    createDirs();
    netSetup(5460,&w);

    return a.exec();
}

void createDirs()
{
    //检查文件夹是否存在，不存在则创建
    QDir *checkDir=new QDir();
    bool exist;
    QString dir=QApplication::applicationDirPath();

    QString dirs[] = {
        "/Key",
        "/Tmp",
        "/Key/AES",
        "/Key/RSA",
        "/Key/Certi"
    };
    for(QString d:dirs)
    {
        exist = checkDir->exists(dir+d);
        if(!exist) checkDir->mkdir(dir+d);
    }
}

void netSetup(quint16 port,QWidget* ctx)
{
    //NetServer* server = new NetServer(port,ctx);
    //server->start();

}
