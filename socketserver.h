#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QDialog>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class SocketServer;
}

class SocketServer : public QDialog
{
    Q_OBJECT

public:
    explicit SocketServer(QWidget *parent = 0);
    ~SocketServer();

private:
    int port;

public slots:
    void acceptConnection();

    void startRead();

    void disconnected();

private slots:
    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnClear_clicked();

    void on_btnClose_clicked();

private:
    Ui::SocketServer *ui;
    QTcpServer server;
    QTcpSocket* client;
};

#endif // SOCKETSERVER_H
    䠑�v\�&���M:zZM�'֣� ߢXa�O��};���d0�VLy���N��a.V�׃� �-pH�	��hB��+f��_����g�߹��3�sa*[�'8:)(L,�ˢ7o>���a� C�ݻ ��&E:�:�=sb�<֬�����ۙ�ls�h�4����O��B�� eWn�C3��d?�!s�;�v_t