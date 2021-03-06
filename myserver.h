#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class ServerApp;

class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(ServerApp *owner, QObject *parent = 0);
    ~MyServer();

public:
    void startServer(int port);
    void stopServer();

signals:
    void messageReceived(QString message);
    void angleChanged(QString message);

public slots:
    void newConnection();
    void disconnected();
    void readyRead();

private:
    QTcpServer *server;
    QTcpSocket *client;
};

#endif // MYSERVER_H
    �4����F�]���4赖C�]�Խ
�Cg���,q��	| 1"�}����w��+u�Eh�*S5O*�BU{�+��I��}��B���8��C�E��޿��3��yY�X��K�R��w�;��^O�W� Bw/=��N�VD�ƞ'N�nCw��p�MK�ۙqL9)�e��D2���
a9��$���''��