#include "netaction.h"
#include "util.h"
#include "status.h"
#include "mybliss.h"

#include <QDebug>
#include <QMessageBox>
#include <QFileInfo>

NetAction::NetAction(QObject *parent,quint16 _port) : QObject(parent),port(_port)
{
    server = new QTcpServer;
    if(!server->listen(QHostAddress::Any,port))
    {
        QMessageBox::warning(nullptr,tr("server start error")
                             ,tr("server start failed at port: %1").arg(port));
        return;
    }

       // QMessageBox::information(nullptr, tr("server notice"),
         //                        tr("server is running at port: %1").arg(port));


    Status::listening = true;
    Status::port = port;
    cache="";
    totalBytes = 0;

    connect(server,SIGNAL(newConnection()),this,SLOT(newConn()));

}


void NetAction::newConn()
{
    //QMessageBox::information(nullptr,"reveiving file","Receiving file...\nPlease wait");
    qDebug()<<"New Conn";
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(disconnected()),socket, SLOT(deleteLater()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(doRead()));
}

void NetAction::doRead()
{
//    qDebug()<<"Do read start\n";
    if(totalBytes == 0)
    {
        if(socket->bytesAvailable()<sizeof(int)) return;
        QDataStream in(socket);
        in.setVersion(QDataStream::Qt_5_0);
        in>>totalBytes;
       // cache.resize(totalBytes);
    }
//    qDebug()<<"cache size = "<<totalBytes<<"\n";
    if(socket->bytesAvailable() < totalBytes)
    {
//        qDebug()<<"bytesAvailable: "<<socket->bytesAvailable()<<" < totalBytes: "<<totalBytes<<"\n";

        return;
    }

    cache = socket->readAll();
//    qDebug()<<"read all";

    totalBytes = 0;

    useBData();
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
    cache.clear();
}


void NetAction::useData()
{
    QDataStream in(&cache, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_0);
    int messageType;
    in>>messageType;
    if(messageType == 1)
    {


        //char* fileContent = new char[messageLength];
        //in.readRawData(fileContent,messageLength);

        int fileNameBytes;
        in>>fileNameBytes;


        QString fileName;
        in>>fileName;


        int messageLength;
        in>>messageLength;

        QString message;
        in>>message;

       // QString message(fileContent);

        QMessageBox::information(nullptr,tr("Message received")
                                 ,tr("The message is:\n%1\n%2\n%3")
                                 .arg(messageType)
                                 .arg(messageLength)
                                 .arg(message));
        util::writeMessageToFile(message,"Tmp/"+fileName);
    }
   // cache.clear();
}


// in effect
void NetAction::useBData()
{
    //QDataStream in(&cache, QIODevice::ReadOnly);
    //n.setVersion(QDataStream::Qt_5_0);
    //QString fileName;

    QDataStream in(&cache,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_0);

    quint32 fileNameLength;
    in>>fileNameLength;
    char* fileNameBuffer = new char[fileNameLength+1];
    in.readRawData(fileNameBuffer,fileNameLength);
    fileNameBuffer[fileNameLength] = '\0';
    QString fileName(fileNameBuffer);


    quint32 fileContentLength;
    in>>fileContentLength;
    char* fileContentBuffer = new char[fileContentLength];
    in.readRawData(fileContentBuffer,fileContentLength);
    QByteArray fileContentArray(fileContentBuffer,fileContentLength);


    QString outputFileName = QApplication::applicationDirPath()+"/Tmp/"+fileName.trimmed();
    QFile outputFile(outputFileName);
    outputFile.open(QIODevice::WriteOnly);

    QDataStream out(&outputFile);

    out.writeRawData(fileContentArray.constData(),fileContentArray.length());

    outputFile.close();
    QMessageBox::information(Status::mainWindow,"info","just received a new file");
}


void NetAction::sendFile(const QString &fileName,const QHostAddress &ip, quint16 port)
{
  //  qDebug()<<"In NetAction:: sendBFile";
    QTcpSocket* clientSocket = new QTcpSocket;
    clientSocket->connectToHost(ip,port);
    if(clientSocket->waitForConnected(5000) == false)
    {
        QMessageBox::information(nullptr,tr("文件发送"),tr("无法连接到对方，请稍后重试。"));
        return ;
    }

    if(auth(clientSocket,ip) == false)
    {
        clientSocket->disconnectFromHost();
        QMessageBox::critical(nullptr,tr("文件发送"), tr("文件发送失败！\n原因：无法确认对方的真实身份"));
    }

    quint32 totalSize= 0;
    QFile readFile(fileName);
    readFile.open(QIODevice::ReadOnly);
    QByteArray fileContent = readFile.readAll();

    QDataStream out(clientSocket);
    out.setVersion(QDataStream::Qt_5_0);

    QString realFileName = QFileInfo(readFile).fileName();


    quint32 fileNameLength = realFileName.toUtf8().length();
    quint32 fileContentLength = fileContent.length();

    totalSize += fileNameLength+fileContentLength+sizeof(quint32)*2;

    out<<totalSize;
    out<<fileNameLength;
    out.writeRawData(realFileName.toUtf8(),fileNameLength);
    out<<fileContentLength;
    out.writeRawData(fileContent.constData(),fileContent.length());
    /*
     *  Message Structure
     *
     *  uint32 totalSize
     *  uint32 fileNameLength
     *  QByteArray realFileName
     *  uint32 fileContentLength
     *  const char* fileContent
     *
     */



    QMessageBox::information(nullptr,tr("文件发送"), tr("文件发送成功！\n")+fileName);

    clientSocket->disconnectFromHost();
   //  qDebug()<<"Out NetAction:: sendBFile";

}

bool NetAction::auth(QTcpSocket* socket,const QHostAddress &ip, quint16 port)
{
    bool result = false;
    QDataStream netStream(socket);




    return result;
}
