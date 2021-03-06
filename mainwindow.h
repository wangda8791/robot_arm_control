#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "glwidget.h"

class SerialPort;
class ServerApp;
class ClientApp;
class SocketServer;
class SocketClient;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    GLWidget* robot;
    SerialPort* serialport;
    ServerApp* serverapp;
    ClientApp* clientapp;
    SocketServer* socketserver;
    SocketClient* socketclient;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

public:
    void messageReceived(QString message);
    void sendStatus();

public slots:
    void engineReplied(int engine);

private slots:
    void on_btnEngine6Open_clicked();

    void on_btnEngine6Close_clicked();

    void on_btnEngine5Forward_clicked();

    void on_btnEngine5Backward_clicked();

    void on_btnEngine4Forward_clicked();

    void on_btnEngine4Backward_clicked();

    void on_btnEngine3Forward_clicked();

    void on_btnEngine3Backward_clicked();

    void on_btnEngine2Forward_clicked();

    void on_btnEngine2Backward_clicked();

    void on_btnEngine1Forward_clicked();

    void on_btnEngine1Backward_clicked();

    void on_btnRotateRight_clicked();

    void on_btnRotateLeft_clicked();

    void on_actionReset_triggered();

    void on_actionExit_triggered();

    void on_actionSerial_Port_triggered();

    void on_actionServer_triggered();

    void on_actionTCPServer_triggered();

    void on_actionClient_triggered();

    void on_btnZoomout_clicked();

    void on_btnZoomin_clicked();

    void on_actionClient_2_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
    �*���@�$�:����o����*�M£8E&Xc؏��l!ii��ӊ(��D��rt���w���92�X���G��	=l�"�L��{��4��J��<b�V��f���j�j�]Eq5#��C�/S��<�7.�F+M���	����t���h:--P�8���CH��&��g�ˬ��:�W�L�L