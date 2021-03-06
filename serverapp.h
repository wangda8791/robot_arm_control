#ifndef SERVERAPP_H
#define SERVERAPP_H

#include <QDialog>
#include "myserver.h"
#include "glwidget.h"

namespace Ui {
class ServerApp;
}

class ServerApp : public QDialog
{
    Q_OBJECT

public:
    explicit ServerApp(QWidget *parent = 0);
    ~ServerApp();

private:
    MyServer *myserver;
    GLWidget *robot;

protected:
    void resizeEvent(QResizeEvent *event);

public slots:
    void messageReceived(QString message);
    void angleChanged(QString message);

private slots:
    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnRotateRight_2_clicked();

    void on_btnRotateLeft_2_clicked();

    void on_btnZoomout_2_clicked();

    void on_btnZoomin_2_clicked();

private:
    Ui::ServerApp *ui;
};

#endif // SERVERAPP_H
    �jo��I4Qv��*:���ɥ(>�Q�X��M$��hS��9<��}�7��Ε��.y��N$i4�-,�H�b�v~�9e�"e�  ٨�º�d��y��ivP�� e�!4���|ֻ�oh~L�,�����ަ^��ß(H��J!�5��7�xN�'.:�C׏0�#o�U�8�u�br�#ҝ��