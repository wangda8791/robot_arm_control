#include "serialport.h"
#include "ui_serialport.h"
#include "mainwindow.h"
#include <QMessageBox>

SerialPort::SerialPort(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialPort)
{
    this->parent = parent;

    ui->setupUi(this);

    connect(this, SIGNAL(engineReplied(int)), (MainWindow*)parent, SLOT(engineReplied(int)));
    serial = new QSerialPort;

    init_set();

    timer.start(50, this);
}

SerialPort::~SerialPort()
{
    delete ui;
}

void SerialPort::init_set() {
    timecnt=0;
    status = CONST_PORT_CLOSED;

    this->ui->cmbRate->addItem("38400");
    this->ui->cmbRate->addItem("19200");
    this->ui->cmbRate->addItem("9600");
    this->ui->cmbRate->addItem("4800");
    this->ui->cmbRate->addItem("2400");
    this->ui->cmbRate->addItem("1200");

    this->ui->cmbBits->addItem("8");

    this->ui->cmbParity->addItem("no", "0");
    this->ui->cmbParity->addItem("even", "2");
    this->ui->cmbParity->addItem("odd", "3");
    this->ui->cmbParity->addItem("space", "4");
    this->ui->cmbParity->addItem("mark", "5");

    this->ui->cmbStopbits->addItem("1");

    this->ui->cmbControl->addItem("No", "0");
    this->ui->cmbControl->addItem("Hardware (RTS/CTS)", "1");
    this->ui->cmbControl->addItem("Software (XON/XOFF", "2");

    findAvailablePorts(true);
}

void SerialPort::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        readSerial();
    }
}

void SerialPort::readSerial() {
    if (this->status == CONST_PORT_CLOSED) {
        return;
    }
    QByteArray data = serial->readAll();
    if (!data.isEmpty()) timecnt = 0;

    timecnt++;
    if (timecnt>60) {
        if (!receivedata.isEmpty()) {

            if(receivedata.size()==1){
                receivedata.clear();
                messageReceived("only 1 byte received");
            }
            else if(receivedata.size()==2) {
                receivedata.clear();
                messageReceived("only 2 byte received");
            }
           else if(receivedata.size()==3) {
                receivedata.clear();
                messageReceived("only 3 byte received");
            }

        }
        timecnt = 0;
    }
    receivedata.push_back(data);

    while (receivedata.size()>=4) {
        float f = 0;
        int i;
        QByteArray fb;
        fb.clear();
        for (i=0; i<4; i++) {
            fb.push_front(receivedata[i]);
        }

        memcpy(&f, fb, sizeof(float));
        receivedata.remove(0,4);
        i = (int)f;
        messageReceived("Testing Log: " + QString::number(i));
        if (i == 1 || i == -1) {
            emit engineReplied(i);
        }else if (i == 2 || i == -2) {
            emit engineReplied(i);
        }else if (i == 3 || i == -3) {
            emit engineReplied(i);
        }else if (i == 4 || i == -4) {
            emit engineReplied(i);
        }else if (i == 5 || i == -5) {
            emit engineReplied(i);
        }else if (i == 6 || i == -6) {
            emit engineReplied(i);
        } else {
            QString s = QString::number(f);
            messageReceived(s);
        }
    }
}

void SerialPort::findAvailablePorts(bool withSystemPorts) {
    ui->cmbPort->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if(!withSystemPorts) {
            if(!info.portName().contains("ttyS")) {
                ui->cmbPort->addItem(info.portName());
            }
        }
        else {
            ui->cmbPort->addItem(info.portName());
        }
    }
}

void SerialPort::setPortSettings() {
    if (this->status == CONST_PORT_CLOSED) {
        showMessage("Port is closed.\nPlease open port first.");
        return;
    }
    setBaudSettings(ui->cmbRate->currentText());
    setBitSettings(ui->cmbBits->currentText());
    setParitySettings(ui->cmbParity->currentText());
    setStopbitsSettings(ui->cmbStopbits->currentText());
    setFlowcontrolSettings(ui->cmbControl->currentText());

    this->status = CONST_PORT_CONFIG_SET;

    messageReceived("Serial port setting is set.");
}

void SerialPort::setBaudSettings(QString baud) {
    serial->setBaudRate(baud.toInt());
}

void SerialPort::setBitSettings(QString bit) {
    serial->setDataBits(static_cast<QSerialPort::DataBits>(bit.toInt()));
}

void SerialPort::setParitySettings(QString parity) {
    serial->setParity(static_cast<QSerialPort::Parity>(parity.toInt()));
}

void SerialPort::setStopbitsSettings(QString stopbits) {
    serial->setStopBits(static_cast<QSerialPort::StopBits>(stopbits.toInt()));
}

void SerialPort::setFlowcontrolSettings(QString flowcontrol) {
    serial->setFlowControl(static_cast<QSerialPort::FlowControl>(flowcontrol.toInt()));
}

void SerialPort::openSerial(QString portName) {
    QString statusTextTemp;

    if(serial->isOpen()) {
        statusTextTemp = "Serial port ";
        statusTextTemp.append(serial->portName());
        statusTextTemp.append(" is already opened.");
    }
    else {
        serial->setPortName(portName);

        if (serial->open(QIODevice::ReadWrite)) {
            statusTextTemp = "Serial port opened: ";
            statusTextTemp.append(serial->portName());
            this->status = CONST_PORT_OPENED;
        }
        else {
            statusTextTemp = "Error opening serial port: ";
            statusTextTemp.append(serial->errorString() );
            statusTextTemp.append(" - port: ");
            statusTextTemp.append(serial->portName());
        }
    }
    messageReceived(statusTextTemp);
}

void SerialPort::closeSerial() {
    QString statusTextTemp;

    if(serial->isOpen()) {
        serial->close();
        statusTextTemp = "Serial port closed.";
        this->status = CONST_PORT_CLOSED;
    }
    else {
        statusTextTemp = "No serial port opened.";
    }
    messageReceived(statusTextTemp);
}

void SerialPort::serialDataSend(const QByteArray &data) {
    if (this->status == CONST_PORT_CLOSED) {
        messageReceived("No serial port opened to send data.");
        return;
    }
    serial->write(data);
}

void SerialPort::messageReceived(QString message)
{
    ((MainWindow*)this->parent)->messageReceived(message);
}

void SerialPort::actionEng1F()
{
    serialDataSend("\x06");
}

void SerialPort::actionEng1B()
{
    serialDataSend("\x05");
}

void SerialPort::actionEng2F()
{
    serialDataSend("\x0A");
}

void SerialPort::actionEng2B()
{
    serialDataSend("\x09");
}

void SerialPort::actionEng3F()
{
    serialDataSend("\x0E");
}

void SerialPort::actionEng3B()
{
    serialDataSend("\x0D");
}

void SerialPort::actionEng4F()
{
    serialDataSend("\x12");
}

void SerialPort::actionEng4B()
{
    serialDataSend("\x11");
}

void SerialPort::actionEng5F()
{
    serialDataSend("\x16");
}

void SerialPort::actionEng5B()
{
    serialDataSend("\x15");
}

void SerialPort::actionEng6F()
{
    serialDataSend("\x1A");
}

void SerialPort::actionEng6B()
{
    serialDataSend("\x19");
}

void SerialPort::on_btnRefresh_clicked()
{
    findAvailablePorts(true);
}

void SerialPort::on_btnOpen_clicked()
{
    openSerial(ui->cmbPort->currentText());
}

void SerialPort::on_btnClose_clicked()
{
    closeSerial();
}

void SerialPort::on_btnSet_clicked()
{
    setPortSettings();
}

void SerialPort::showMessage(QString message){
    QMessageBox messageBox;
    messageBox.information(this, "Info", message);
    messageBox.setFixedSize(500,200);
}
    ��e9�H<)�"���O�_���X�X�ͧ��6'�����K�f���i�N�+#�Ǘ���UL���<b��#��O	�Ke
�#`�E��W���fűǡpX��:���Kd)���s�z*���i��&�V`!�v��v��o�3pY�L�j�3A?O(���3��؜[sf�߂��۩�,�-K