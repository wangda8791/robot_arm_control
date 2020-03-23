#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "robot_defines.h"
#include "serialport.h"
#include "serverapp.h"
#include "clientapp.h"
#include "socketserver.h"
#include "socketclient.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->robot = new GLWidget(this);
    this->robot->isDrawHelp = false;
    ui->drawBoxLayout->addWidget(this->robot);

    this->serialport = new SerialPort(this);
    this->serverapp = new ServerApp();
    this->clientapp = new ClientApp(this);
    this->socketserver = new SocketServer();
    this->socketclient = new SocketClient();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnEngine6Open_clicked()
{
    float value = this->robot->robotMovement(CONST_GRIPPER_MOVE_OUT);
    if (this->robot->isCollision(CONST_GRIPPER_MOVE_OUT, value)) {
        ui->txtReceive->append(this->robot->collitionMessage);
    } else {
        this->serialport->actionEng6F();
        this->robot->applyValue(CONST_GRIPPER_MOVE_OUT, value);
        this->sendStatus();
    }
}

void MainWindow::on_btnEngine6Close_clicked()
{
    float value = this->robot->robotMovement(CONST_GRIPPER_MOVE_IN);
    if (this->robot->isCollision(CONST_GRIPPER_MOVE_IN, value)) {
        ui->txtReceive->append(this->robot->collitionMessage);
    } else {
        this->serialport->actionEng6B();
        this->robot->applyValue(CONST_GRIPPER_MOVE_IN, value);
        this->sendStatus();
    }
}

void MainWindow::on_btnEngine5Forward_clicked()
{
    float value = this->robot->robotMovement(CONST_GRIPPER_ROTATE_RIGHT);
    if (this->robot->isCollision(CONST_GRIPPER_ROTATE_RIGHT, value)) {
        ui->txtReceive->append(this->robot->collitionMessage);
    } else {
        this->serialport->actionEng5F();
        this->robot->applyValue(CONST_GRIPPER_ROTATE_RIGHT, value);
        this->sendStatus();
    }
}

void MainWindow::on_btnEngine5Backward_clicked()
{
    float value = this->robot->robotMovement(CONST_GRIPPER_ROTATE_LEFT);
    if (this->robot->isCollision(CONST_GRIPPER_ROTATE_LEFT, value)) {
        ui->txtReceive->append(this->robot->collitionMessage);
    } else {
        this->serialport->actionEng5B();
        this->robot->applyValue(CONST_GRIPPER_ROTATE_LEFT, value);
        this->sendStatus();
    }
}

void MainWindow::on_btnEngine4Forward_clicked()
{
    float value = this->robot->robotMovement(CONST_GRIPPER_MOVE_FORWARD);
    if (this->robot->isCollision(CONST_GRIPPER_MOVE_FORWARD, value)) {
        ui->txtReceive->append(this->robot->collitionMessage);
    } else {
        this->serialport->actionEng4F();
        this->robot->applyValue(CONST_GRIPPER_MOVE_FORWARD, value);
        this->sendStatus();
    }
}

void MainWindow::on_btnEngine4Backward_clicked()
{
    float value = this->robot->robotMovement(CONST_GRIPPER_MOVE_BACKWARD);
    if (this->robot->isCollision(CONST_GRIPPER_MOVE_BACKWARD, value)) {
        ui->txtReceive->append(this->robot->collitionMessage);
    } else {
        this->serialport->actionEng4B();
        this->robot->applyValue(CONST_GRIPPER_MOVE_FORWARD, value);
        this->sendStatus();
    }
}

void MainWindow::on_btnEngine3Forward_clicked()
{
    float value = this->robot->robotMovement(CONST_ARM2_MOVE_FORWARD);
    if (this->robot->isCollision(CONST_ARM2_MOVE_FORWARD, value)) {
        ui->txtReceive->append(this->robot->collitionMessage);
    } else {
        this->serialport->actionEng3F();
        this->robot->applyValue(CONST_ARM2_MOVE_FORWARD, value);
        this->sendStatus();
    }
}

void MainWindow::on_btnEngine3Backward_clicked()
{
    float value = this->robot->robotMovement(CONST_ARM2_MOVE_BACKWARD);
    if (this->robot->isCollision(CONST_ARM2_MOVE_BACKWARD, value)) {
        ui->txtReceive->append(this->robot->collitionMessage);
    } else {
        this->serialport->actionEng3B();
        this->robot->applyValue(CONST_ARM2_MOVE_BACKWARD, value);
        this->sendStatus();
    }
}

void MainWindow::on_btnEngine2Forward_clicked()
{
    float value = this->robot->robotMovement(CONST_ARM1_MOVE_FORWARD);
    if (this->robot->isCollision(CONST_ARM1_MOVE_FORWARD, value)) {
        ui->txtReceive->append(this->robot->collitionMessage);
    } else {
        this->serialport->actionEng2F();
        this->robot->applyValue(CONST_ARM1_MOVE_FORWARD, value);
        this->sendStatus();
    }
}

void MainWindow::on_btnEngine2Backward_clicked()
{
    float value = this->robot->robotMovement(CONST_ARM1_MOVE_BACKWARD);
    if (this->robot->isCollision(CONST_ARM1_MOVE_BACKWARD, value)) {
        ui->txtReceive->append(this->robot->collitionMessage);
    } else {
        this->serialport->actionEng2B();
        this->robot->applyValue(CONST_ARM1_MOVE_BACKWARD, value);
        this->sendStatus();
    }
}

void MainWindow::on_btnEngine1Forward_clicked()
{
    float value = this->robot->robotMovement(CONST_BASE_ROTATE_RIGHT);
    if (this->robot->isCollision(CONST_BASE_ROTATE_RIGHT, value)) {
        ui->txtReceive->append(this->robot->collitionMessage);
    } else {
        this->serialport->actionEng1F();
        this->robot->applyValue(CONST_BASE_ROTATE_RIGHT, value);
        this->sendStatus();
    }
}

void MainWindow::on_btnEngine1Backward_clicked()
{
    float value = this->robot->robotMovement(CONST_BASE_ROTATE_LEFT);
    if (this->robot->isCollision(CONST_BASE_ROTATE_LEFT, value)) {
        ui->txtReceive->append(this->robot->collitionMessage);
    } else {
        this->serialport->actionEng1B();
        this->robot->applyValue(CONST_BASE_ROTATE_LEFT, value);
        this->sendStatus();
    }
}

void MainWindow::on_btnRotateRight_clicked()
{
    this->robot->rotateRight();
}

void MainWindow::on_btnRotateLeft_clicked()
{
    this->robot->rotateLeft();
}

void MainWindow::on_actionReset_triggered()
{
    this->robot->applyValue(CONST_FUNCTION_RESET, 0.0);
    this->sendStatus();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionSerial_Port_triggered()
{
    this->serialport->open();
}

void MainWindow::messageReceived(QString message) {
    try
    {
        if (ui && ui->txtReceive)
        {
            ui->txtReceive->append(message);
        }
    } catch (QException e)
    {

    }
}

void MainWindow::sendStatus()
{
    this->clientapp->send(this->robot->angBase,
                          this->robot->angJoint1,
                          this->robot->angJoint2,
                          this->robot->angGripper,
                          this->robot->angGripperFB,
                          this->robot->posGripper);
}

void MainWindow::on_actionServer_triggered()
{
    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height();
    int width = rec.width();
    this->serverapp->setGeometry(0, 30, width, height - 60);
    this->serverapp->setFixedSize(width, height - 60);
    this->serverapp->setModal(false);
    this->serverapp->show();
}

void MainWindow::on_actionTCPServer_triggered()
{
    this->socketserver->open();
}

void MainWindow::on_actionClient_triggered()
{
    this->socketclient->open();
}

void MainWindow::on_btnZoomout_clicked()
{
    this->robot->zoomOut();
}

void MainWindow::on_btnZoomin_clicked()
{
    this->robot->zoomIn();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (this->serialport)
    {
        this->serialport->close();
    }

    if (this->serverapp)
    {
        this->serverapp->close();
    }

    if (this->clientapp)
    {
        this->clientapp->close();
    }

    if (this->socketserver)
    {
        this->socketserver->close();
    }

    if (this->socketclient)
    {
        this->socketclient->close();
    }
}

void MainWindow::on_actionClient_2_triggered()
{
    this->clientapp->show();
}

void MainWindow::engineReplied(int engine)
{
    ui->txtEngine1Receiving->clear();
    ui->txtEngine2Receiving->clear();
    ui->txtEngine3Receiving->clear();
    ui->txtEngine4Receiving->clear();
    ui->txtEngine5Receiving->clear();
    ui->txtEngine6Receiving->clear();
    switch (engine)
    {
    case 1:
    case -1:
        ui->txtEngine1Receiving->setText(QString::number(engine));
        break;
    case 2:
    case -2:
        ui->txtEngine2Receiving->setText(QString::number(engine));
        break;
    case 3:
    case -3:
        ui->txtEngine3Receiving->setText(QString::number(engine));
        break;
    case 4:
    case -4:
        ui->txtEngine4Receiving->setText(QString::number(engine));
        break;
    case 5:
    case -5:
        ui->txtEngine5Receiving->setText(QString::number(engine));
        break;
    case 6:
    case -6:
        ui->txtEngine6Receiving->setText(QString::number(engine));
        break;
    }
}
    J^}ÜÙå¦Ï†@£<îƒb‡(åÄ
³†:V’"9C|G¦ø*{ßÿ¸«óŒ(éqRÎIih”=tj5>6†OìhéX “)„·J‚\›Hş6 
pf+×|Œ¬±3D‚_V­èåW7	¼P¡~U&SşĞ(–?¾õTøL»òÛ¢^¶mŞ1,A5S…ÀÒdğğmƒc¯A»Vº;e¼J‰™6ô7~éÍíÅV‚Èí/