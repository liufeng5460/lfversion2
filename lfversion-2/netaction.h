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
    explicit NetAction(QObject *parent = 0,quint16 _port=5460);

    //sended use static function
    static void sendFile(const QString& fileName,const QHostAddress& ip, quint16 port=5460);
    static bool auth(QTcpSocket* clientSocket ,const QHostAddress& ip, quint16 port=5460);

    // receiver use non-static function
    void useData();
    void useCipherData();
    bool authed();


public slots:
    void newConn();
    void startRead();
private:

    static bool waitData(quint32 size,QTcpSocket* socket);
    static MyAES netAES;
    void doRead();




    QByteArray cache;
    quint16 port;
    QTcpServer* server;
    QTcpSocket* serverSocket;
    quint32 totalBytes;
};

#endif // NETACTION_H
