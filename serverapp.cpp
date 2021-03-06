#include "serverapp.h"
#include "ui_serverapp.h"
#include <QMessageBox>

ServerApp::ServerApp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerApp)
{
    ui->setupUi(this);
    this->myserver = new MyServer(this);
    this->robot = new GLWidget(this);
    this->robot->isDrawHelp = true;
    ui->drawBoxLayout->addWidget(this->robot);
}

ServerApp::~ServerApp()
{
    delete ui;
}

void ServerApp::on_btnStart_clicked()
{
    this->myserver->startServer(ui->txtPort->text().toInt());
}

void ServerApp::on_btnStop_clicked()
{
    this->myserver->stopServer();
}

void ServerApp::messageReceived(QString message)
{
    QMessageBox messageBox;
    messageBox.information(this, "Info", message);
    messageBox.setFixedSize(500,200);
}

void ServerApp::angleChanged(QString message)
{
    QRegExp rx("[, ]");
    QStringList list = message.split(rx, QString::SkipEmptyParts);

    this->robot->angBase = list.at(0).toFloat();
    this->robot->angJoint1 = list.at(1).toFloat();
    this->robot->angJoint2 = list.at(2).toFloat();
    this->robot->angGripper = list.at(3).toFloat();
    this->robot->angGripperFB = list.at(4).toFloat();
    this->robot->posGripper = list.at(5).toFloat();

    this->robot->adjustValues();
}

void ServerApp::resizeEvent(QResizeEvent *event)
{
    QRect rect(0, 0, this->width(), this->height());
    ui->drawBoxWidget->setGeometry(rect);
}

void ServerApp::on_btnRotateRight_2_clicked()
{
    this->robot->rotateRight();
}

void ServerApp::on_btnRotateLeft_2_clicked()
{
    this->robot->rotateLeft();
}

void ServerApp::on_btnZoomout_2_clicked()
{
    this->robot->zoomOut();
}

void ServerApp::on_btnZoomin_2_clicked()
{
    this->robot->zoomIn();
}
    �Ü7<QO0ݯ���&��M�g����"�&�L����"e���%�&��sZ�9�(��BN'4�,���nN�qL��|E�+9�?SwEZ��C3�'SBh���ti2� ��Q�4ӓy)�E'"yN(2|:w�Y�dҮ�k���.e�%��󚯋��h�|�d�Ux�\6bh"�N�@oY�h