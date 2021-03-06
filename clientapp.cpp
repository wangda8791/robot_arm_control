#include "clientapp.h"
#include "ui_clientapp.h"
#include "mainwindow.h"

ClientApp::ClientApp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientApp)
{
    ui->setupUi(this);
    this->parent = parent;

    connect(&client, SIGNAL(connected()), this, SLOT(connected()));
    connect(&client, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

ClientApp::~ClientApp()
{
    client.close();
    delete ui;
}

void ClientApp::on_Connect_clicked()
{
    QHostAddress addr(ui->ip->text());
    client.connectToHost(addr, ui->port->text().toInt());
}

void ClientApp::connected()
{
    ((MainWindow*)this->parent)->messageReceived("Controller is connected to server app.");
    ((MainWindow*)this->parent)->sendStatus();
}

void ClientApp::disconnected()
{
    ((MainWindow*)this->parent)->messageReceived("Controller is disconnected from server app.");
}

void ClientApp::on_Disconnect_clicked()
{
    client.close();
}

void ClientApp::send(float angEngine1, float angEngine2, float angEngine3, float angEngine4, float angEngine5, float angEngine6)
{
    if (!client.isOpen()) return;
    QString msg = QString("%1,%2,%3,%4,%5,%6").arg(QString::number(angEngine1),
                                                   QString::number(angEngine2),
                                                   QString::number(angEngine3),
                                                   QString::number(angEngine4),
                                                   QString::number(angEngine5),
                                                   QString::number(angEngine6));
    QByteArray msgByte = msg.toLatin1().toHex();
    quint32 length = msgByte.length();
    client.write((char*)&length, sizeof(length));
    client.write(msgByte, msgByte.length());
}
    ���~����0O�/p�H�0*�[���_U��{�V�Egm;e6 �Y�F%.;"��?(/�%���]��nH���`ESh�P����h�A%�y��_]���r-rf[����k�.��/f��Xy�|�'�Q�M��Gaf�<B�L�Ҕ[W��`X�儌���I�?��K���9+D��}��p߾Q˪�3��