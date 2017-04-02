#include "netserver.h"
#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QTextStream>
NetServer::NetServer(quint16 p,QWidget* ctx):
    port(p),
    readingFlag(NoRead)
{
    context = ctx;
}

NetServer::~NetServer()
{

}

bool NetServer::start()
{
    server = new QTcpServer();
    if (!server->listen(QHostAddress::Any, port)) {
           QMessageBox::critical(context, tr("Network Error "),
                                 tr("Unable to listening at port: %1.\nSystem prompt: %2")
                                   );
            return false;
    }else{
        QMessageBox::information(context,tr("Start listening network"),
                                 tr("Start listening at port: %1.").arg(port));
    }
    connect(server, SIGNAL(newConnection()), this,SLOT(newConn()));
    return true;
}

void NetServer::newConn()
{
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(disconnected()),
            socket, SLOT(deleteLater()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(prepareRead()));
}

void NetServer::prepareRead()
{
    if(readingFlag != NoRead)
    {
        switch (readingFlag)
        {
            case ReadingFile:
                readFile();
                return;
        }
    }

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_0);
    if(socket->bytesAvailable()<sizeof(int)) return;
    int messageType;
    in>>messageType;
    switch(messageType){
        case 1:
            readingFlag = ReadingFile;
            readFile();
            return;
    }

}

void NetServer::readFile()
{
    int fileSize;
    if(socket->bytesAvailable()<sizeof(fileSize)) return;

    QDataStream in(socket);
    in>>fileSize;
    if(socket->bytesAvailable()<<fileSize) return;

    QString fileContent;
    in>>fileContent;

    int fileNameSize;
    if(socket->bytesAvailable()<sizeof(fileNameSize)) return;

    QString fileName;
    in>>fileName;
    socket->close();


     /** Write file content to harddisk **/
    QFile acceptedFile(QApplication::applicationDirPath()+"/"+fileName);
    acceptedFile.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&acceptedFile);
    out<<fileContent;
    acceptedFile.close();
}
