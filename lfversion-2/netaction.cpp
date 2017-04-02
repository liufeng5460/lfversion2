#include "netaction.h"
#include "util.h"
#include <QDebug>
#include <QMessageBox>

NetAction::NetAction(QObject *parent,quint16 _port) : QObject(parent),port(_port)
{
    server = new QTcpServer;
    if(!server->listen(QHostAddress::Any,port))
    {
        QMessageBox::warning(nullptr,tr("server start error")
                             ,tr("server start failed at port: %1").arg(port));
        return;
    }
    else
    {
        QMessageBox::information(nullptr, tr("server notice"),
                                 tr("server is running at port: %1").arg(port));
    }

    cache="";
    totalBytes = 0;

    connect(server,SIGNAL(newConnection()),this,SLOT(newConn()));

}


void NetAction::newConn()
{
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(disconnected()),socket, SLOT(deleteLater()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(doRead()));
}

void NetAction::doRead()
{
    qDebug()<<"Do read start\n";
    if(totalBytes == 0)
    {
        if(socket->bytesAvailable()<sizeof(int)) return;
        QDataStream in(socket);
        in.setVersion(QDataStream::Qt_5_0);
        in>>totalBytes;
        cache.resize(totalBytes);
    }
    qDebug()<<"cache size = "<<totalBytes<<"\n";
    if(socket->bytesAvailable() < totalBytes)
    {
        qDebug()<<"bytesAvailable: "<<socket->bytesAvailable()<<" < totalBytes: "<<totalBytes<<"\n";

        return;
    }

    cache = socket->readAll();
    qDebug()<<"read all";

    totalBytes = 0;

    useData2();
}


void NetAction::useData2()
{
    QDataStream in(&cache, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_0);
    int messageLength;
    in>>messageLength;
    QString message;
    in>>message;
    QMessageBox::information(nullptr,tr("Message received")
                                 ,tr("The message is:\n%1\n%2")
                                 .arg(messageLength)
                                 .arg(message));

    util::writeMessageToFile(message,"Tmp/tmp.txt");
}


void NetAction::useData()
{
    QDataStream in(&cache, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_0);
    int messageType;
    in>>messageType;
    if(messageType == 1)
    {
        int messageLength;
        in>>messageLength;

        QString message;
        in>>message;

        QMessageBox::information(nullptr,tr("Message received")
                                 ,tr("The message is:\n%1\n%2\n%3")
                                 .arg(messageType)
                                 .arg(messageLength)
                                 .arg(message));
    }
}

void NetAction::sendMessage(QHostAddress& ip, quint16 port)
{
    QTcpSocket* clientSocket = new QTcpSocket;
    clientSocket->connectToHost(ip,port);

    QByteArray dataBlock;
    QDataStream out(&dataBlock,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);


    QString message = QString::fromUtf8("但是值得思考的问题是");
    out<<(int)(sizeof(int)+message.toUtf8().length());
    out<<message.toUtf8().length()<<message;

    clientSocket->write(dataBlock);
    clientSocket->disconnectFromHost();
}

