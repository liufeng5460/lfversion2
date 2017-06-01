#ifndef NETACTION_H
#define NETACTION_H
#include "myaes.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
class NetAction : public QObject
{
    Q_OBJECT
public:
    explicit NetAction(QObject *parent = 0);
    ~NetAction();
    //sended use static function
    static bool sendFile(const QString& fileName,const QHostAddress& ip,int port,bool safe=true);
    static bool sendFile(const QString& peerName,const QString& fileName,const QHostAddress& ip,int port,bool safe=true);
    static bool  sendFilePlain(const QString& fileName,const QHostAddress& ip, int port);
    static bool auth(QTcpSocket* clientSocket ,const QHostAddress& ip);

    // receiver use non-static function
    void useData();
    void useCipherData();
    bool authed();


public slots:
    void newConn();
    void startRead();
private:

    static bool waitData(quint32 size,QTcpSocket* socket);
    void doRead();
    void doReadPlain();


    static MyAES netAES;
    static bool doAuth;
    static QString peerName;


    QByteArray cache;
    quint16 port;
    QTcpServer* server;
    QTcpSocket* serverSocket;
    quint32 totalBytes;
};

#endif // NETACTION_H
