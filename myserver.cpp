#include "myserver.h"
#include "serverapp.h"


MyServer::MyServer(ServerApp *owner, QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    client = NULL;

    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
    connect(this,SIGNAL(messageReceived(QString)),owner,SLOT(messageReceived(QString)));
    connect(this,SIGNAL(angleChanged(QString)),owner,SLOT(angleChanged(QString)));
}

void MyServer::startServer(int port)
{
    if (server->isListening()) {
        emit messageReceived("Server is already started.");
        return;
    }

    if(!server->listen(QHostAddress::Any,port))
    {
        emit messageReceived("Error: " + server->errorString());
    } else {
        emit messageReceived("Server started successfully.");
    }
}

void MyServer::stopServer()
{
    if (server->isListening())
    {
        server->close();
        if (client != NULL && client->isOpen()) {
            client->close();
            client = NULL;
        }
        emit messageReceived("Server stopped successfully.");
    } else {
        emit messageReceived("Server is not started .");
    }
}

void MyServer::newConnection()
{
    client = server->nextPendingConnection();

    connect(client, SIGNAL(readyRead()), SLOT(readyRead()));
    connect(client, SIGNAL(disconnected()), SLOT(disconnected()));
}

void MyServer::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());

    char buffer[1024] = {0};
    quint32 length = 0;

    if (socket->bytesAvailable() < 4)
    {
        if (!socket->waitForReadyRead(-1)) {
            return;
        }
    }

    socket->read((char*)&length, sizeof(length));

    while (socket->bytesAvailable() < length)
        socket->waitForReadyRead(-1);

    quint32 read = 0;

    QString message = "";
    do
    {
        read += socket->read(buffer, length);
        message += QString::fromLatin1(QByteArray::fromHex(buffer));
    } while (read < length);

    emit angleChanged(message);
}
void MyServer::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    socket->deleteLater();
    client = NULL;
}

MyServer::~MyServer()
{

}

    ~���~Che7��
��{;��=�!���۶n�`���De)l�{'}u����r�.πD&,-�3$I����`n;��S������R���\;���K4�iSz�KO����Nj���M�����	^����o\z�-(�hy��|���R��5ɔ��[Ź�u$�ne�5�9�:l"��{˱=����2O