#include "socketclient.h"
#include "ui_socketclient.h"
#include <QHostAddress>

SocketClient::SocketClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SocketClient)
{
    ui->setupUi(this);
}

SocketClient::~SocketClient()
{
    client.close();
    delete ui;
}

void SocketClient::on_btnClear_clicked()
{
    ui->Console->clear();
}

void SocketClient::on_btnClose_clicked()
{
    close();
}

void SocketClient::on_Connect_clicked()
{
    QHostAddress addr(ui->ip->text());
    client.connectToHost(addr, ui->port->text().toInt());
    ui->Console->append("Connecting to server ...");
}

void SocketClient::on_Disconnect_clicked()
{
    client.close();
    ui->Console->append("Disconnected from server ...");
}

void SocketClient::on_Send_clicked()
{
    QString msg = ui->Message->text();
    ui->Console->append("Sending message to server :" + msg);

    QByteArray msgByte = msg.toLatin1().toHex();
    quint32 length = msgByte.length();
    client.write((char*)&length, sizeof(length));
    client.write(msgByte, msgByte.length());

    ui->Message->clearFocus();
}
    L/T���=n���Y�QX9&��̂���2W�F�rQ�ҞĴB����Gm���b��}�qӿ�w~C!����7��B�?�|�([���+�P�Q���@s��?���W��7������ յ"� vLuZ��7����;�tP��*,�����8�}������2��u���Ɂ]`