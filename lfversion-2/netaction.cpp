#include "netaction.h"
#include "util.h"
#include "status.h"
#include "mybliss.h"
#include "myaes.h"
#include "mylwe.h"

#include <QDebug>
#include <QMessageBox>
#include <QFileInfo>
#include <iostream>
using std::cout;
using std::endl;

MyAES NetAction::netAES = MyAES();
bool NetAction::doAuth = true;
QString NetAction::peerName;

NetAction::NetAction(QObject *parent) : QObject(parent)
{

    port = Status::conf["port"].toInt();
    server = new QTcpServer;
    if(!server->listen(QHostAddress::Any,port))
    {
        QMessageBox::warning(nullptr,tr("server start error")
                             ,tr("server start failed at port: %1").arg(port));
        return;
    }

       // QMessageBox::information(nullptr, tr("server notice"),
         //                        tr("server is running at port: %1").arg(port));

    Status::conf["listenning"] = "true";
    cache="";
    totalBytes = 0;

    connect(server,SIGNAL(newConnection()),this,SLOT(newConn()));

}

NetAction::~NetAction()
{
    server->close();
}

void NetAction::newConn()
{
    //QMessageBox::information(nullptr,"reveiving file","Receiving file...\nPlease wait");
    qDebug()<<"New Conn";
    serverSocket = server->nextPendingConnection();
    connect(serverSocket, SIGNAL(disconnected()),serverSocket, SLOT(deleteLater()));
    connect(serverSocket, SIGNAL(readyRead()), this, SLOT(startRead()));
}

void NetAction::doReadPlain()
{
    quint32 totalBytes;
    QDataStream out(&cache,QIODevice::WriteOnly);
    QDataStream in(serverSocket);
    in.setVersion(QDataStream::Qt_5_0);
    out.setVersion(QDataStream::Qt_5_0);

    if(!waitData(sizeof(totalBytes), serverSocket)) return;
    in>>totalBytes;

    if(!waitData(totalBytes,serverSocket)) return;
    cache = serverSocket->read(totalBytes);
//    cout<<"cache size: "<<cache.size()<<endl;
    useData();
}

void NetAction::doRead()
{
    char flag;
    serverSocket->getChar(&flag);
    if(flag == '0')
    {
        doReadPlain();
        return;
    }
    if(authed() == false)
    {
        return;
    }

    if(!waitData(sizeof(totalBytes), serverSocket)) return;
    QDataStream in(serverSocket);
    in.setVersion(QDataStream::Qt_5_0);
    in>>totalBytes;

    cout<<"In reveicer:\n"
       <<"totalBytes: "<<totalBytes
      <<endl;
    if(!waitData(totalBytes,serverSocket)) return;
    cache = serverSocket->read(totalBytes);
    cout<<"cache size: "<<cache.size()<<endl;

//    useData();
    useCipherData();
}

void NetAction::useCipherData()
{
    string cipherString = cache.toStdString();
    cout<<"In reveicer:\n"
       <<"cipherString length: "<<cipherString.length()
      <<endl;

    string plainString = netAES.Decrypt(cipherString);

    QByteArray buffer = QByteArray::fromHex(QByteArray(plainString.c_str()));
    QDataStream in(&buffer,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_0);


    quint32 totalSize;
    in>>totalSize;

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


    QString outputFileName = Status::fileDir+fileName.trimmed();
    QFile outputFile(outputFileName);
    outputFile.open(QIODevice::WriteOnly);

    QDataStream out(&outputFile);

    out.writeRawData(fileContentArray.constData(),fileContentArray.length());

    outputFile.close();
    QMessageBox::information(Status::mainWindow,"文件传输","接受到一个新文件");
}

void NetAction::useData()
{
    // use plain data
    /*
     *  cache structure
     * quint32 fileNameLength
     * char* fileName
     * quint32 fileContentLength
     * char* fileContent
     *
     */

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
    QMessageBox::information(Status::mainWindow,"文件传输","接受到一个新文件");
}


bool NetAction::sendFile(const QString &fileName,const QHostAddress &ip,int port,bool safe)
{
  //  qDebug()<<"In NetAction:: sendBFile";
    QTcpSocket* clientSocket = new QTcpSocket;
    clientSocket->connectToHost(ip,port);
    if(clientSocket->waitForConnected(5000) == false)
    {
        QMessageBox::information(nullptr,tr("文件发送"),tr("无法连接到对方，请稍后重试。"));
        return false;
    }

    clientSocket->write("1"); // tell receiver this is a safe transfer
    clientSocket->flush();

    MyAES aes;
    if(auth(clientSocket,ip) == false)
    {
        clientSocket->disconnectFromHost();
        QMessageBox::critical(nullptr,tr("文件发送"), tr("文件发送失败！\n原因：无法确认对方的真实身份"));
        return false;
    }

    quint32 totalSize= 0;
    QFile readFile(fileName);
    readFile.open(QIODevice::ReadOnly);
    QByteArray fileContent = readFile.readAll();

    QByteArray buffer;
    //QDataStream out(clientSocket);
    QDataStream out(&buffer, QIODevice::WriteOnly);
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

     QString bufferString(buffer.toHex());
     string cipherBufferString = netAES.Encrypt(bufferString.toStdString());
     out.setDevice(clientSocket);
     out<<static_cast<int>(cipherBufferString.length());
     out.writeRawData(cipherBufferString.c_str(), cipherBufferString.length());
     cout<<"In sender:\n"
        <<"cipher string length: "<<cipherBufferString.length()
       <<endl;
     clientSocket->flush();


    QMessageBox::information(nullptr,tr("文件发送"), tr("文件发送成功！\n")+fileName);

    clientSocket->disconnectFromHost();
   //  qDebug()<<"Out NetAction:: sendBFile";
    return true;

}

bool NetAction::sendFile(const QString &peerName, const QString &fileName, const QHostAddress &ip, int port, bool safe)
{
    NetAction::peerName = peerName;
    if(safe)
    {
        return sendFile(fileName,ip,port);
    }
    else
    {
        return sendFilePlain(fileName,ip,port);
    }
}

bool NetAction::sendFilePlain(const QString &fileName, const QHostAddress &ip,int port)
{

    QTcpSocket* clientSocket = new QTcpSocket;
    clientSocket->connectToHost(ip,port);
    if(clientSocket->waitForConnected(5000) == false)
    {
        QMessageBox::information(nullptr,tr("文件发送"),tr("无法连接到对方，请稍后重试。"));
        return false;
    }

    clientSocket->write("0"); // tell receiver this is a plain transfer
    clientSocket->flush();

    quint32 totalSize= 0;
    QFile readFile(fileName);
    readFile.open(QIODevice::ReadOnly);
    QByteArray fileContent = readFile.readAll();

    QDataStream out(clientSocket);
//    QDataStream out(&buffer, QIODevice::WriteOnly);
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

    clientSocket->flush();
    QMessageBox::information(nullptr,tr("文件发送"), tr("文件发送成功！\n")+fileName);

    clientSocket->disconnectFromHost();
    return true;

}

bool NetAction::auth(QTcpSocket* socket, const QHostAddress &ip)
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
    socket->flush();

//    PRINT_DEBUG_INFO("auth")

    // receive sig and lwe.pk
    signature4io* sig = new signature4io;
    if(!waitData(sizeof(signature4io),socket)) return false;

    long long temp;
    for(int i=0 ;i<BlissN;i++)
    {
        netStream>>temp;
        sig->z1[i] = static_cast<long>(temp);
        netStream>>temp;
        sig->z2[i] = static_cast<long>(temp);
        netStream>>temp;
        sig->z1High[i] = static_cast<long>(temp);
        netStream>>temp;
        sig->z1Low[i] =  static_cast<long>(temp);
        netStream>>temp;
        sig->z2Carry[i] = static_cast<long>(temp);
    }
    for(int i=0 ;i<kappa; i++)
    {
        netStream>>temp;
        sig->indicesC[i] = static_cast<long>(temp);
    }

    if(!waitData(sizeof(uint16_t)*static_cast<quint32>(LWE_M*2),socket)) return false;
    MyLWE lwe;
    for(int i=0; i<LWE_M; i++)
    {
        netStream>>lwe.pk1[i]
                 >>lwe.pk2[i];
    }


    pubkey4io* blissPk = MyBliss::getPubkey(Status::certiDir+peerName+"_sendFile.cer",true);
    result = Decision(blissPk,sig,lwe.pk1,lwe.pk2, miu);

    // send result;
    netStream<<result;
    socket->flush();

    if(result == true)
    {
        // generate aes
        netAES.GenerateKey(16);
        string key,iv;
        netAES.getKey(key,iv);

        cout<<"In client(key sended):\n"
            <<key<<endl
            <<iv<<endl;

        // encrypt aes key and iv
        QByteArray encryptedKey;
        MyLWE::encryptMessage(lwe.pk1,lwe.pk2,QByteArray(key.c_str()),encryptedKey);
        QByteArray encryptedIv;
        MyLWE::encryptMessage(lwe.pk1,lwe.pk2,QByteArray(iv.c_str()),encryptedIv);

        // send aes key and iv
        netStream<<encryptedKey.size();
        netStream.writeRawData(encryptedKey.constData(), encryptedKey.size());
        netStream<<encryptedIv.size();
        netStream.writeRawData(encryptedIv.constData(), encryptedIv.size());
        socket->flush();
    }

    delete blissPk;
    delete sig;
    delete[] miu;

//    qDebug()<<"In auth: result is "<<result;

//    return result;
    return true;
}

bool NetAction::authed()
{

    QDataStream netStream(serverSocket);
    netStream.setVersion(QDataStream::Qt_5_0);

    // get miu
    if(!waitData(sizeof(unsigned char)*SHA512_DIGEST_LENGTH, serverSocket)) return false;
    unsigned char* miu = new unsigned char[SHA512_DIGEST_LENGTH];
    for(int i=0; i<SHA512_DIGEST_LENGTH; i++)
    {
        netStream>>miu[i];
    }

//    PRINT_DEBUG_INFO("authed")


    // compute answer
    MyBliss bliss;
    bliss.load("my_sendFile.pk","my_sendFile.sk");
    signature4io* sig = new signature4io;
    MyLWE lwe;
    lwe.generateKey();
    Answer(bliss.pk,bliss.sk,sig,lwe.pk1,lwe.pk2,miu);

    // send sig
    for(int i=0 ;i<BlissN;i++)
    {
        netStream<<static_cast<qint64>(sig->z1[i])
                 <<static_cast<qint64>(sig->z2[i])
                 <<static_cast<qint64>(sig->z1High[i])
                 <<static_cast<qint64>(sig->z1Low[i])
                 <<static_cast<qint64>(sig->z2Carry[i]);
    }
    for(int i=0 ;i<kappa; i++)
    {
        netStream<<static_cast<qint64>(sig->indicesC[i]);
    }
    serverSocket->flush();

    // send pk
    for(int i=0; i<LWE_M; i++)
    {
        netStream<<lwe.pk1[i]
                 <<lwe.pk2[i];
    }
    serverSocket->flush();

    bool result;
    // get result
    if(!waitData(sizeof(int), serverSocket)) return false;
    netStream>>result;

    if(result == true)
    {


        int size;
        // get aes key
        if(!waitData(sizeof(int), serverSocket)) return false;
        netStream>>size;
        if(!waitData(static_cast<quint32>(size),serverSocket)) return false;
        char* encryptedKeyBytes = new char[size];
        netStream.readRawData(encryptedKeyBytes, size);
        QByteArray encryptedKeyArray(encryptedKeyBytes,size);
        QByteArray keyArray;
        lwe.decrypt(keyArray,encryptedKeyArray);
        string key = keyArray.toStdString();

        // get aes iv
        if(!waitData(sizeof(int), serverSocket)) return false;
        netStream>>size;
        if(!waitData(static_cast<quint32>(size),serverSocket)) return false;
        char* encryptedIvBytes = new char[size];
        netStream.readRawData(encryptedIvBytes, size);
        QByteArray encryptedIvArray(encryptedIvBytes,size);
        QByteArray ivArray;
        lwe.decrypt(ivArray,encryptedIvArray);
        string iv = ivArray.toStdString();

        cout<<"In server(key receiver):\n"
            <<key<<endl
            <<iv<<endl;

        netAES.setKey(key,iv);
    }


    delete sig;
    delete[] miu;
    return result;
}
bool NetAction::waitData(quint32 size,QTcpSocket* socket)
{
    while(socket->bytesAvailable() < size)
    {
        if(socket->waitForReadyRead(Status::waitTime) == false)
        {
            QMessageBox::critical(nullptr,"文件传输","文件传输失败：\n持续超过"+QString::number(Status::waitTime/1000)+"秒无法获取数据，请检查网络状况后重试");
            return false;
            // this->thread()->exit(0);
        }
    }
    return true;
}

void NetAction::startRead()
{
    disconnect(serverSocket, SIGNAL(readyRead()), this, SLOT(startRead()));
   // QtConcurrent::run(this,&NetAction::doRead);
    doRead();
}
