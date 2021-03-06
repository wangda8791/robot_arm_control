
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    float robotMovement(int movement);
    void rotateLeft();
    void rotateRight();
    void zoomIn();
    void zoomOut();
    void adjustValues();
    bool isCollision(int movement, float angle);
    void applyValue(int movement, float angle);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    void drawArms();
    void drawHelp();

    void perspectiveProjection();
    void orthographicProjection();

    void resetValues();
    void trimValue(float &val, float minVal, float maxVal);
    void rewindValue(float &val, float minVal, float maxVal);

public:
    QString collitionMessage;
    bool isDrawHelp;
    float angBase;
    float angJoint1;
    float angJoint2;
    float angGripper;
    float angGripperFB;
    float posGripper;

private:
    qreal aspect;

    bool floorCollision;
    bool socketCollision;
    bool arm1Collision;
    bool arm2Collision;
    bool gripperCollision;

    float posEye;

    float angX;
    float angY;
    float angZ;

    QPoint lastPos;
    QColor qtGreen;
    QColor qtPurple;
    QColor qtLightBlueGray;

    bool   loaded;
};

#endif
    ��$&�ʶ���離��5��F�9Fz{Ѯh\A,�,q�"�Bc����U�d��vL�n���E?�i���}���.�tկ�Qy�z�Z����	�[��˼�nj��A���n)r}zߞZψRͰ�B5cU���߶������\'���c��87X_�0/,�^������?��1{.<���Bѧ�p��