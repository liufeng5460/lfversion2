#ifndef NETSERVER_H
#define NETSERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>
#include <QObject>
class NetServer : public QObject
{
    Q_OBJECT
public:
    explicit NetServer(quint16 p,QWidget* ctx);
    ~NetServer();
    bool start();

private:
    enum ReadingState{
        NoRead,
        ReadingFile
    } readingFlag;

    QWidget* context;
    quint16 port;
    QTcpServer *server;
    QTcpSocket *socket;

    void readFile();

private slots:
    void newConn();
    void prepareRead();

};

#endif // NETSERVER_H
