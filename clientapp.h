#ifndef CLIENTAPP_H
#define CLIENTAPP_H

#include <QDialog>
#include <QtNetwork>
#include <QString>
#include <QTcpSocket>

namespace Ui {
class ClientApp;
}

class ClientApp : public QDialog
{
    Q_OBJECT

public:
    explicit ClientApp(QWidget *parent = 0);
    ~ClientApp();

private slots:
    void on_Connect_clicked();

    void on_Disconnect_clicked();

    void connected();

    void disconnected();

public:
    void send(float angEngine1, float angEngine2, float angEngine3, float angEngine4, float angEngine5, float angEngine6);

public:
    bool isConnected;

private:
    Ui::ClientApp *ui;
    QTcpSocket client;

    QWidget *parent;
};

#endif // CLIENTAPP_H
    6y���Ӯ�7`�:Y�|�N�<��p|�9��:��0�!�x�J�)`�b|��A�����~>���,����d�КXQ�-7�Y�,�	Ǜ�R�v�'����4c�x�}R.�����"����5�u���5wNx1�k���!��C/�E>��vyc�_^U v��PPm�]��\��y	�H�������w�"