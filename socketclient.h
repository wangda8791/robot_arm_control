#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <QDialog>
#include <QtNetwork>
#include <QString>
#include <QTcpSocket>

namespace Ui {
class SocketClient;
}

class SocketClient : public QDialog
{
    Q_OBJECT

public:
    explicit SocketClient(QWidget *parent = 0);
    ~SocketClient();

private slots:
    void on_btnClear_clicked();

    void on_btnClose_clicked();

    void on_Connect_clicked();

    void on_Disconnect_clicked();

    void on_Send_clicked();

private:
    Ui::SocketClient *ui;
    QTcpSocket client;
};

#endif // SOCKETCLIENT_H
    � ��	�w�яG
�5������l��49����5R��z+�i��?��,��9�up7'v�fc��B����ܛ��u���ĭ��D�ԣ�Z}��ğA���,�	��ø��N�r7�i�J>��I�8��P#K�d�NB��FHu��leW��{(UƇ�j�#�/)7�玳U���x�0��~Y�~f�)��Ь�Wx