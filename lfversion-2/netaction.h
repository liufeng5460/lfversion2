#ifndef NETACTION_H
#define NETACTION_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
class NetAction : public QObject
{
    Q_OBJECT
public:
    explicit NetAction(QObject *parent = 0,quint16 _port=5460);
    static void sendMessage(QByteArray& dataBlock,const QHostAddress& ip, quint16 port=5460);
    static void sendFile(const QString& fileName,const QHostAddress& ip, quint16 port=5460);
    static void sendBFile(const QString& fileName,const QHostAddress& ip, quint16 port=5460);
    void useBData();
    void useData();
    void useData2();


signals:

public slots:
    void newConn();
    void doRead();
private:

    QByteArray cache;
    quint16 port;
    QTcpServer* server;
    QTcpSocket* socket;
    int totalBytes;
};

#endif // NETACTION_H
