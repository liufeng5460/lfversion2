#include "netaction.h"
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
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_0);
    if(socket->bytesAvailable()<sizeof(int)) return;
    int messageType;
    in>>messageType;
    QMessageBox::information(nullptr,tr("Message received")
                             ,tr("The message is:\n%1").arg(messageType));
}

void NetAction::sendMessage(QHostAddress& ip, quint16 port)
{
    QTcpSocket* clientSocket = new QTcpSocket;
    clientSocket->connectToHost(ip,port);

    QByteArray dataBlock;
    QDataStream out(&dataBlock,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    int messageType = 1;
    out<<messageType;

    clientSocket->write(dataBlock);
    clientSocket->disconnectFromHost();



}

