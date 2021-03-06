#-------------------------------------------------
#
# Project created by QtCreator 2016-07-11T15:09:27
#
#-------------------------------------------------

QT +=serialport core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

TARGET = RobotArm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    serialport.cpp \
    serverapp.cpp \
    myserver.cpp \
    socketclient.cpp \
    socketserver.cpp \
    clientapp.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    robot_defines.h \
    tiny_obj_loader.h \
    serialport.h \
    serverapp.h \
    myserver.h \
    socketclient.h \
    socketserver.h \
    clientapp.h

FORMS    += mainwindow.ui \
    serialport.ui \
    serverapp.ui \
    socketclient.ui \
    socketserver.ui \
    clientapp.ui

RESOURCES += \
    Resources.qrc

OTHER_FILES += \
    Images/rotate_left.png \
    Images/rotate_right.png
    KIʿ�$_92��S�*Q%$��}C�Ψb�>��)D����o�i��=	�J�5X�9�9a�\g'g9y���=���\�PL��M��}�C~�]��3��}�y���ek����{������ZQEvO\dn�Q��:��1���bs�}�Cۻ�����N�N[Q&?��_m�O�Y���E� [��-ɘ