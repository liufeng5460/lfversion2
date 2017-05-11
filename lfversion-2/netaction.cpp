#include "netaction.h"
#include "util.h"
#include "status.h"
#include "mybliss.h"
#include "mylwe.h"

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
    if(authed() == false)
    {
        return;
    }
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

    useData();
}


void NetAction::useData()
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
        return;
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
    netStream.setVersion(QDataStream::Qt_5_0);

    // send miu
    unsigned char* miu = new unsigned char[SHA512_DIGEST_LENGTH];
    Challenge(miu);
    for(int i=0;i<SHA512_DIGEST_LENGTH; i++)
    {
        netStream<<miu[i];
    }


    // receive sig and lwe.pk
    signature4io* sig = new signature4io;
    while(socket->bytesAvailable()<sizeof(signature4io))
    {
        socket->waitForReadyRead();
    }

    for(int i=0 ;i<BlissN;i++)
    {
        netStream>>(qint64)sig->z1[i]
                 >>sig->z2[i]
                 >>sig->z1High[i]
                 >>sig->z1Low[i]
                 >>sig->z2Carry[i];
    }

    while(socket->bytesAvailable()<sizeof(uint16_t)*LWE_M*2)
    {
        socket->waitForReadyRead();
    }
    MyLWE lwe;
    for(int i=0; i<LWE_M; i++)
    {
        netStream>>lwe.pk1[i]
                 >>lwe.pk2[i];
    }

    pubkey4io blissPk = MyBliss.getPubkey("byebye");
    result = Decision(blissPk,sig,lwe.pk1,lwe.pk2, miu);

    delete blissPk;
    delete sig;
    delete[] miu;
    return result;
}

bool NetAction::authed()
{
    QDataStream netStream(socket);
    netStream.setVersion(QDataStream::Qt_5_0);

    // get miu
    while(socket->bytesAvailable()<sizeof(unsigned char)*SHA512_DIGEST_LENGTH)
    {
        socket->waitForReadyRead();
    }
    unsigned char* miu = new unsigned char[SHA512_DIGEST_LENGTH];
    for(int i=0; i<SHA512_DIGEST_LENGTH; i++)
    {
        netStream>>miu[i];
    }

    // compute answer
    MyBliss bliss;
    bliss.load("byebye","byebye");
    signature4io* sig = new signature4io;
    MyLWE lwe;
    lwe.generateKey();
    Answer(bliss.pk,bliss.sk,sig,lwe.pk1,lwe.pk2,miu);

    // send sig
    for(int i=0 ;i<BlissN;i++)
    {
        netStream<<sig->z1[i]
                 <<sig->z2[i]
                 <<sig->z1High[i]
                 <<sig->z1Low[i]
                 <<sig->z2Carry[i];
    }
    for(int i=0 ;i<kappa; i++)
    {
        netStream<<sig->indicesC[i];
    }

    for(int i=0; i<LWE_M; i++)
    {
        netStream<<lwe.pk1[i]
                 <<lwe.pk2[i];
    }


    // get result
    while(socket->bytesAvailable() <sizeof(int))
    {
        socket->waitForReadyRead();
    }
    netStream>>result;


    delete sig;
    delete[] miu;

    if(result == 1) return true;
    return false;
}
