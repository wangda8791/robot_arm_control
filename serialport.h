#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QBasicTimer>
#include "robot_defines.h"

namespace Ui {
class SerialPort;
}

class SerialPort : public QDialog
{
    Q_OBJECT

public:
    explicit SerialPort(QWidget *parent = 0);
    ~SerialPort();

public:
    void actionEng1F();
    void actionEng1B();
    void actionEng2F();
    void actionEng2B();
    void actionEng3F();
    void actionEng3B();
    void actionEng4F();
    void actionEng4B();
    void actionEng5F();
    void actionEng5B();
    void actionEng6F();
    void actionEng6B();

private:
    void init_menu(int);
    void init_set();
    void findAvailablePorts(bool withSystemPorts);
    void setPortSettings();
    void openSerial(QString portName);
    void readSerial();
    void closeSerial();
    void serialDataSend(const QByteArray &data);
    void sendSerialOpen();
    void setBaudSettings(QString baud);
    void setBitSettings(QString bit);
    void setParitySettings(QString parity);
    void setStopbitsSettings(QString stopbits);
    void setFlowcontrolSettings(QString flowcontrol);
    void messageReceived(QString message);
    void showMessage(QString message);

private slots:
    void on_btnRefresh_clicked();
    void on_btnOpen_clicked();
    void on_btnClose_clicked();
    void on_btnSet_clicked();

signals:
    void engineReplied(int engine);

protected:
    void timerEvent(QTimerEvent *event);

private:
    Ui::SerialPort *ui;
    QSerialPort *serial;
    QBasicTimer timer;
    QByteArray receivedata;
    int timecnt;
    int status;
    QWidget *parent;
};

#endif // SERIALPORT_H
    GW���f���8���8�_��%�U�bn��qB4�z��( �����9p��N��I瀺��S��~aAEzd��b��|z`>��f� U� ad�p�u'��,|�;��� ��{�u��V��������=>�$(G/L�%��#yIC���'Ea�	Ǘ�ʂ��(���%�D�Zn$|�:������/�?(�M2�8IwX