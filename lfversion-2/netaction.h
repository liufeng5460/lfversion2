#ifndef NETACTION_H
#define NETACTION_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
class NetAction : public QObject
{
    Q_OBJECT
public:
    explicit NetAction(QObject *parent = 0,quint16 _port=5460);
    static void sendMessage(QHostAddress& ip, quint16 port=5460);


signals:

public slots:
    void newConn();
    void doRead();
private:
    quint16 port;
    QTcpServer* server;
    QTcpSocket* socket;
};

#endif // NETACTION_H
