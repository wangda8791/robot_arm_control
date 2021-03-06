#include "socketserver.h"
#include "ui_socketserver.h"

SocketServer::SocketServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SocketServer)
{
    ui->setupUi(this);
    connect(&server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    port = -1;
}

SocketServer::~SocketServer()
{
    server.close();
    delete ui;
}

void SocketServer::on_btnStart_clicked()
{
    if (server.isListening()) {
        ui->txtLog->append("Server is already started with port " + QString::number(port) + ".");
        return;
    }

    if (!server.listen(QHostAddress::Any, ui->txtPort->text().toInt()))
    {
        ui->txtLog->append("Error: " + server.errorString());
    } else {
        ui->txtLog->append("Port " + ui->txtPort->text() + " is opened.");
        port = ui->txtPort->text().toInt();
    }
}

void SocketServer::on_btnStop_clicked()
{
    if (server.isListening()) {
        server.close();
        ui->txtLog->append("Port " + QString::number(port) + " is closed.");
    } else {
        ui->txtLog->append("No opened port.");
    }
}

void SocketServer::acceptConnection()
{
    client = server.nextPendingConnection();
    ui->txtLog->append("Connected to client.");

    connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void SocketServer::disconnected() {
    ui->txtLog->append("Disconnected from client.");
}

void SocketServer::startRead()
{
    char buffer[1024] = {0};
    quint32 length = 0;

    if (client->bytesAvailable() < 4)
    {
        if (!client->waitForReadyRead(-1)) {
            return;
        }
    }

    client->read((char*)&length, sizeof(length));

    while (client->bytesAvailable() < length)
        client->waitForReadyRead(-1);

    quint32 read = 0;

    QString message = "Message received from client:";
    do
    {
        read += client->read(buffer, 2);
        QString character = buffer;
        int ascii = character.toInt(0, 16);
        message += QString::number(ascii, 2);
    } while (read < length);

    ui->txtLog->append(message);
}

void SocketServer::on_btnClear_clicked()
{
    ui->txtLog->clear();
}

void SocketServer::on_btnClose_clicked()
{
    close();
}
    �k��c��ݶ��fm��:>&1!���s_$�|8�h����(,� t�ʻm]�*2���M��yQW�����"!}� ��9�l����N�Ж?n�����S�=*]A�5�L_�Z9e�8Ӻ׫5�%�����_�/��4RD=&��f����}�֗� �Y�u�~z������m����;G��ʎ