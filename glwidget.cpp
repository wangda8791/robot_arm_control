
#include <QtWidgets>
#include <QtOpenGL>
#include <QDebug>
#include <QMessageBox>
#include <math.h>

#include "glwidget.h"
#include "robot_defines.h"

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"

std::vector<tinyobj::shape_t> g_shapes;
std::vector<tinyobj::material_t> g_materials;

tinyobj::shape_t * objBaseCylinder;
tinyobj::shape_t * objBasePlate;
tinyobj::shape_t * objArm1;
tinyobj::shape_t * objArm2;
tinyobj::shape_t * objArm3;
tinyobj::shape_t * objArm4;
tinyobj::shape_t * objSection1;
tinyobj::shape_t * objSection2;
tinyobj::shape_t * objSection3;
tinyobj::shape_t * objGripper1;
tinyobj::shape_t * objGripper2;
tinyobj::shape_t * objRodCenter;
tinyobj::shape_t * objRodMid;

void shiftObject(tinyobj::shape_t* obj, float dx, float dy, float dz)
{
    for(int v = 0; v < obj->mesh.positions.size() / 3; v++) {
        obj->mesh.positions[3*v+0] += dx;
        obj->mesh.positions[3*v+1] += dy;
        obj->mesh.positions[3*v+2] += dz;
    }
}

bool initObjects()
{
    QString sObj = QApplication::applicationDirPath() + "/" + QString(OBJ_FileName);
    QFile qrcObj(sObj);
    QTemporaryFile file;
    bool ret = FALSE;
    std::string err;

    if (qrcObj.open(QFile::ReadOnly) && file.open()) {
        file.write(qrcObj.readAll());
        ret = tinyobj::LoadObj(g_shapes, g_materials, err, file.fileName().toStdString().c_str());
    }
    if(!ret) {
        QMessageBox::warning(NULL, OBJ_FileName, "There is no object file\n"+QString(OBJ_FileName));
        return false;
    }

    for(int i = 0; i < g_shapes.size(); i++) {
        tinyobj::shape_t* shape = &g_shapes[i];

        if(shape->name.compare(Name_BaseCylinder) == 0){
            objBaseCylinder = shape;
        }
        else if(shape->name.compare(Name_BasePlate) == 0) {
            objBasePlate = shape;
        }
        else if(shape->name.compare(Name_Arm1) == 0) {
            shiftObject(shape, 0, -Joint1_Height, 0);
            objArm1 = shape;
        }
        else if(shape->name.compare(Name_Arm2) == 0) {
            shiftObject(shape, 0, -Joint1_Height, 0);
            objArm2= shape;
        }
        else if(shape->name.compare(Name_RodMid) == 0) {
            shiftObject(shape, 0, -Joint1_Height, 0);
            objRodMid = shape;
        }
        else if(shape->name.compare(Name_Arm3) == 0) {
            shiftObject(shape, 0, -Joint2_Height, 0);
            objArm3 = shape;
        }
        else if(shape->name.compare(Name_Arm4) == 0) {
            shiftObject(shape, 0, -Joint2_Height, 0);
            objArm4 = shape;
        }
        else if(shape->name.compare(Name_Section1) == 0) {
            shiftObject(shape, 0, -Joint2_Height, 0);
            objSection1 = shape;
        }
        else if(shape->name.compare(Name_Section2) == 0) {
            shiftObject(shape, 0, -Gripper_Height, 0);
            objSection2 = shape;
        }
        else if(shape->name.compare(Name_Section3) == 0) {
            shiftObject(shape, 0, -Gripper_Height, 0);
            objSection3 = shape;
        }
        else if(shape->name.compare(Name_Gripper1) == 0) {
            shiftObject(shape, 0, -Gripper_Height, 0);
            objGripper1 = shape;
        }
        else if(shape->name.compare(Name_Gripper2) == 0) {
            shiftObject(shape, 0, -Gripper_Height, 0);
            objGripper2 = shape;
        }
        else if(shape->name.compare(Name_RodCenter) == 0) {
            shiftObject(shape, 0, -Gripper_Height, 0);
            objRodCenter = shape;
        }
    }

    return true;
}

void drawObject(tinyobj::shape_t* obj)
{

    GLfloat *vertices = obj->mesh.positions.data();
    GLfloat *normals = obj->mesh.normals.data();
    GLuint *indices = obj->mesh.indices.data();
    int nums = obj->mesh.indices.size();

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, vertices ); // Set The Vertex Pointer To Our Vertex Data
    glNormalPointer( GL_FLOAT, 0, normals ); // Set The Vertex Pointer To Our Vertex Data
    glDrawElements(GL_TRIANGLES, nums, GL_UNSIGNED_INT, indices);
}


GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
    qtLightBlueGray = QColor::fromRgb(108, 114, 140);

    resetValues();
    loaded = initObjects();
}

GLWidget::~GLWidget()
{
}



QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(800, 800);
}

void GLWidget::initializeGL()
{
    //qglClearColor(qtPurple.dark());
    qglClearColor(qtLightBlueGray);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glShadeModel(GL_SMOOTH);
    glDisable( GL_MULTISAMPLE );

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0};
    GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0};
    GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0};
    GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0};
    GLfloat mShininess[] = {128};

    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width * devicePixelRatio(), height * devicePixelRatio());
    aspect = (qreal)width / (qreal)(height ? height : 1);
    perspectiveProjection();
}

void GLWidget::perspectiveProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-aspect, +aspect, -0.5, +1.5, 4.0, 160.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::orthographicProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, +1.0, -1.0, +1.0, -90.0, +90.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    perspectiveProjection();
    glTranslatef(0.0, 0.0, posEye);
    glRotatef(angX, 1.0, 0.0, 0.0);
    glRotatef(angY, 0.0, 1.0, 0.0);
    glRotatef(angZ, 0.0, 0.0, 1.0);
    drawArms();

    orthographicProjection();
    if (isDrawHelp)
        drawHelp();
}

void GLWidget::drawArms()
{
    if(!loaded)
        return;
    GLfloat blackDiffuseMaterial[] = {0.0, 0.0, 0.0};
    GLfloat orangeDiffuseMaterial[] = {1.0, 0.498, 0.153};
    GLfloat redOrangeDiffuseMaterial[] = {1.0, 0.35, 0.0};
    GLfloat darkOrangeDiffuseMaterial[] = {0.8, 0.2, 0.0};
    GLfloat brownDiffuseMaterial[] = {0.5, 0.25, 0.0};
    GLfloat redBrownDiffuseMaterial[] = {0.5, 0.0, 0.0};
    GLfloat darkRedAmbientMaterial[] = {1.0, 0.0, 0.0};
    GLfloat removeAmbientMaterial[] = {0.0, 0.0, 0.0, 1.0};

    // Draw surface
    glDisable(GL_LIGHTING);
    if (floorCollision) {
        glColor4f(0.5, 0.0, 0.0, 0.2);
    } else {
        glColor3f(0.3, 0.3 ,0.3);
    }
    glBegin(GL_QUADS);
    glVertex3f(-2, 0, -2);
    glVertex3f(-2, 0, 2);
    glVertex3f(2, 0, 2);
    glVertex3f(2, 0, -2);
    glEnd();
    glEnable(GL_LIGHTING);

    // Draw Base Cylinder
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, removeAmbientMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blackDiffuseMaterial);
    drawObject(objBaseCylinder);

    // Draw Rectangle Mark
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(-0.115, 0.2, 0.315);
    glVertex3f(-0.115, 0.7, 0.315);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.09, 0.2, 0.315);
    glVertex3f(0.09, 0.7, 0.315);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-0.115, 0.2, 0.315);
    glVertex3f(0.09, 0.2, 0.315);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-0.115, 0.7, 0.315);
    glVertex3f(0.09, 0.7, 0.315);
    glEnd();
    glEnable(GL_LIGHTING);

    // Draw Base Plate
    if (socketCollision) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkRedAmbientMaterial);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redOrangeDiffuseMaterial);
    } else {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, removeAmbientMaterial);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, orangeDiffuseMaterial);
    }
    glRotatef(angBase, 0.0, 1.0, 0.0);
    drawObject(objBasePlate);

    // Draw Arm1 and Arm2 for Joint1
    glTranslatef(0.0, Joint1_Height, 0.0);
    glRotatef(angJoint1, 1.0, 0.0, 0.0);
    if (arm1Collision) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkRedAmbientMaterial);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, darkOrangeDiffuseMaterial);
    } else {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, removeAmbientMaterial);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, darkOrangeDiffuseMaterial);
    }
    drawObject(objArm1);
    drawObject(objArm2);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, removeAmbientMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blackDiffuseMaterial);
    drawObject(objRodMid);

    // Draw Arm3,Arm4, Section and Grippers for Joint2
    glTranslatef(0.0, Joint2_Height - Joint1_Height, 0.0);
    glRotatef(angJoint2 - angJoint1, 1.0, 0.0, 0.0);
    if (arm2Collision) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkRedAmbientMaterial);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redOrangeDiffuseMaterial);
    } else {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, removeAmbientMaterial);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, orangeDiffuseMaterial);
    }
    drawObject(objArm3);
    drawObject(objArm4);

    // Draw Section2,3 and Grippers for Gripper
    if (gripperCollision) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkRedAmbientMaterial);
    } else {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, removeAmbientMaterial);
    }
    glTranslatef(0.0, Gripper_Height - Joint2_Height - 0.09, 0.0);
    glRotatef(angGripperFB - angJoint2, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -Gripper_Height + Joint2_Height + 0.09, 0.0);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blackDiffuseMaterial);
    drawObject(objSection1);

    glTranslatef(0.0, Gripper_Height - Joint2_Height, 0.0);
    glRotatef(angGripper, 0.0, 1.0, 0.0);

    drawObject(objSection2);
    drawObject(objSection3);
    if (gripperCollision) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redBrownDiffuseMaterial);
    } else {
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial);
    }
    drawObject(objRodCenter);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blackDiffuseMaterial);
    glTranslatef(-(posGripper - 50) / 1000, 0.0, 0.0);
    drawObject(objGripper1);
    glTranslatef(2 * (posGripper - 50) / 1000, 0.0, 0.0);
    drawObject(objGripper2);
}

void GLWidget::drawHelp()
{
    QStringList helps;
    helps << "Engine1: " + QString::number(angBase) + " degree";
    helps << "Engine2: " + QString::number(angJoint1) + " degree";
    helps << "Engine3: " + QString::number(angJoint2) + " degree";
    helps << "Engine4: " + QString::number(angGripper) + " degree";
    helps << "Engine5: " + QString::number(angGripperFB) + " degree";
    helps << "Engine6: " + QString::number(posGripper) + " mm";

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    qglColor(Qt::white);
    for(int i = 0; i < helps.size(); i++) {
        renderText(-0.95, 0.9-i*0.05, 0, helps.at(i), QFont("Courier", 10, QFont::Bold, false) );
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void GLWidget::rotateRight() {
    angY -= sceneAngleStep;
    adjustValues();
}

void GLWidget::rotateLeft() {
    angY += sceneAngleStep;
    adjustValues();
}

void GLWidget::zoomIn() {
    posEye += 1;
    adjustValues();
}

void GLWidget::zoomOut() {
    posEye -= 1;
    adjustValues();
}

float GLWidget::robotMovement(int movement)
{
    float angle = 0.0;

    switch (movement)
    {
    case CONST_ARM1_MOVE_BACKWARD:
        angle = qMax(angJoint1 - Joint1_StepAngle, (float)Joint1_MinAngle);
        break;
    case CONST_ARM1_MOVE_FORWARD:
        angle = qMin(angJoint1 + Joint1_StepAngle, (float)Joint1_MaxAngle);
        break;
    case CONST_ARM2_MOVE_BACKWARD:
        angle = qMax(angJoint2 - Joint2_StepAngle, (float)Joint2_MinAngle);
        break;
    case CONST_ARM2_MOVE_FORWARD:
        angle = qMin(angJoint2 + Joint2_StepAngle, (float)Joint2_MaxAngle);
        break;
    case CONST_GRIPPER_ROTATE_RIGHT:
        angle = qMax(angGripper - Gripper_RotateStepAngle, (float)Gripper_RotateMinAngle);
        break;
    case CONST_GRIPPER_ROTATE_LEFT:
        angle = qMin(angGripper + Gripper_RotateStepAngle, (float)Gripper_RotateMaxAngle);
        break;
    case CONST_GRIPPER_MOVE_BACKWARD:
        angle = qMax(angGripperFB - Gripper_StepAngle, (float)Gripper_MinAngle);
        break;
    case CONST_GRIPPER_MOVE_FORWARD:
        angle = qMin(angGripperFB + Gripper_StepAngle, (float)Gripper_MaxAngle);
        break;
    case CONST_BASE_ROTATE_RIGHT:
        angle = qMax(angBase - Base_StepAngle, (float)Base_MinAngle);
        break;
    case CONST_BASE_ROTATE_LEFT:
        angle = qMin(angBase + Base_StepAngle, (float)Base_MaxAngle);
        break;
    case CONST_GRIPPER_MOVE_OUT:
        angle = qMin(posGripper + Gripper_StepPos, (float)Gripper_MaxPos);
        break;
    case CONST_GRIPPER_MOVE_IN:
        angle = qMax(posGripper - Gripper_StepPos, (float)Gripper_MinPos);
        break;
    }

    return angle;
}

void GLWidget::resetValues()
{
    posEye = -12;
    angX = 25;
    angY = 330;
    angZ = 0;

    angBase = 0;
    angJoint1 = 0;
    angJoint2 = 0;
    angGripper = 0;
    angGripperFB = 0;
    posGripper = 0;

    floorCollision = false;
    socketCollision = false;
    arm1Collision = false;
    arm2Collision = false;
    gripperCollision = false;
}

void GLWidget::adjustValues()
{
    trimValue(posEye, -30, -5);

    rewindValue(angBase, Base_MinAngle, Base_MaxAngle);
    trimValue(angJoint1, Joint1_MinAngle, Joint1_MaxAngle);
    trimValue(angJoint2, Joint2_MinAngle, Joint2_MaxAngle);
    rewindValue(angGripper, Gripper_MinAngle, Gripper_MaxAngle);

    rewindValue(angX, 0, 360);
    rewindValue(angY, 0, 360);
    rewindValue(angZ, 0, 360);

    updateGL();
}

int func_surface(float x)
{
    if (x >= -110 && x<= 100)
        return 360;
    return 0;
}

bool GLWidget::isCollision(int movement, float angle)
{
    floorCollision = false;
    socketCollision = false;
    arm1Collision = false;
    arm2Collision = false;
    gripperCollision = false;

    float p[11][2];
    float l[8] = { 340.0, 220.0, 220.0, 150.0, 145.0, 60.0, 22.5, 82.0 };
    float alpha[6];
    float degree[6] = { angBase, angJoint1, angJoint2, angGripperFB, angGripper, posGripper };

    switch (movement)
    {
    case CONST_ARM1_MOVE_BACKWARD:
        degree[1] = angle;
        break;
    case CONST_ARM1_MOVE_FORWARD:
        degree[1] = angle;
        break;
    case CONST_ARM2_MOVE_BACKWARD:
        degree[2] = angle;
        break;
    case CONST_ARM2_MOVE_FORWARD:
        degree[2] = angle;
        break;
    case CONST_GRIPPER_ROTATE_RIGHT:
        break;
    case CONST_GRIPPER_ROTATE_LEFT:
        break;
    case CONST_GRIPPER_MOVE_BACKWARD:
        degree[3] = angle;
        break;
    case CONST_GRIPPER_MOVE_FORWARD:
        degree[3] = angle;
        break;
    case CONST_BASE_ROTATE_RIGHT:
        break;
    case CONST_BASE_ROTATE_LEFT:
        break;
    case CONST_GRIPPER_MOVE_OUT:
        break;
    case CONST_GRIPPER_MOVE_IN:
        break;
    }

    for (int i=0; i<5; i++) {
        alpha[i] = degree[i] * M_PI / 180;
    }

    p[0][0] = 0;
    p[0][1] = l[0];
    p[1][0] = p[0][0] + l[1] * qSin(alpha[1]);
    p[1][1] = p[0][1] + l[1] * qCos(alpha[1]);
    p[2][0] = p[1][0] + l[2] * qSin(alpha[2]);
    p[2][1] = p[1][1] + l[2] * qCos(alpha[2]);
    p[3][0] = p[2][0] + l[3] * qSin(alpha[3]);
    p[3][1] = p[2][1] + l[3] * qCos(alpha[3]);
    p[4][0] = p[2][0] - l[4] * qSin(alpha[3]);
    p[4][1] = p[2][1] - l[4] * qCos(alpha[3]);
    p[5][0] = p[3][0] + l[5] * qCos(alpha[3]);
    p[5][1] = p[3][1] - l[5] * qSin(alpha[3]);
    p[6][0] = p[3][0] - l[5] * qCos(alpha[3]);
    p[6][1] = p[3][1] + l[5] * qSin(alpha[3]);
    p[7][0] = p[4][0] + l[6] * qCos(alpha[3]);
    p[7][1] = p[4][1] - l[6] * qSin(alpha[3]);
    p[8][0] = p[4][0] - l[6] * qCos(alpha[3]);
    p[8][1] = p[4][1] + l[6] * qSin(alpha[3]);
    p[9][0] = p[5][0] - l[7] * qSin(alpha[3]);
    p[9][1] = p[5][1] - l[7] * qCos(alpha[3]);
    p[10][0] = p[6][0] - l[7] * qSin(alpha[3]);
    p[10][1] = p[6][1] - l[7] * qCos(alpha[3]);

    // #1. Check conflict with floor and socket
    for (int i=1; i<=10; i++) {
        if (func_surface(p[i][0]) >= p[i][1]) {
            if (i == 1) {
                floorCollision = true;
                arm1Collision = true;
                collitionMessage = "Arm1 conflicted with Floor.";
            }
            if (i == 2) {
                if (p[i][1] <= 0) {
                    floorCollision = true;
                    arm2Collision = true;
                    collitionMessage = "Arm2 conflicted with Floor.";
                } else {
                    socketCollision = true;
                    arm2Collision = true;
                    collitionMessage = "Arm2 conflicted with Socket.";
                }
            }
            if (i > 3) {
                if (p[i][1] <= 0) {
                    floorCollision = true;
                    gripperCollision = true;
                    collitionMessage = "Gripper conflicted with Floor.";
                } else {
                    socketCollision = true;
                    gripperCollision = true;
                    collitionMessage = "Gripper conflicted with Socket.";
                }
            }
            updateGL();
            return true;
        }
    }

    // #2. Grabber conflict with arm2
    if (qMin(qAbs(M_PI - (alpha[2]-alpha[3])), qAbs(M_PI - (alpha[3]-alpha[2]))) < 1.1694) {
        arm2Collision = true;
        gripperCollision = true;
        collitionMessage = "Gripper conflicted with Arm2.";
        updateGL();
        return true;
    }

    // #3. Grabber conflict with arm1
    if (p[0][1] - p[1][1] != 0 && p[1][0] - p[0][0] != 0) {
        float a = (p[1][0] * p[0][1] - p[0][0] * p[1][1]) / (p[0][1] - p[1][1]);
        float b = (p[1][0] * p[0][1] - p[0][0] * p[1][1]) / (p[1][0] - p[0][0]);
        if (a != 0) {
            float alpha1_ = qAtan(b/a);
            float whuai1 = M_PI / 2 - alpha1_;
            float p_ = a * qSin(alpha1_);
            float d[11];
            for (int i=2; i<=10; i++) {
                d[i] = p[i][0] * qCos(whuai1) + p[i][1] * qSin(whuai1) - p_;
            }

            for (int i=2; i<=10; i++) {
                if (((p[i][0] > p[0][0] - 35 && p[i][0] < p[1][0] + 35) || (p[i][0] > p[1][0] - 35 && p[i][0] < p[0][0] + 35)) &&
                        ((p[i][1] > p[0][1] && p[i][1] < p[1][1]) || (p[i][1] > p[1][1] && p[i][1] < p[0][1]))) {
                    if (qAbs(d[i]) < 35) {
                        arm1Collision = true;
                        gripperCollision = true;
                        collitionMessage = "Gripper conflicted with Arm1.";
                        updateGL();
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void GLWidget::applyValue(int movement, float angle)
{
    switch (movement)
    {
    case CONST_ARM1_MOVE_BACKWARD:
        angJoint1 = angle;
        break;
    case CONST_ARM1_MOVE_FORWARD:
        angJoint1 = angle;
        break;
    case CONST_ARM2_MOVE_BACKWARD:
        angJoint2 = angle;
        break;
    case CONST_ARM2_MOVE_FORWARD:
        angJoint2 = angle;
        break;
    case CONST_GRIPPER_ROTATE_RIGHT:
        angGripper = angle;
        break;
    case CONST_GRIPPER_ROTATE_LEFT:
        angGripper = angle;
        break;
    case CONST_GRIPPER_MOVE_BACKWARD:
        angGripperFB = angle;
        break;
    case CONST_GRIPPER_MOVE_FORWARD:
        angGripperFB = angle;
        break;
    case CONST_BASE_ROTATE_RIGHT:
        angBase = angle;
        break;
    case CONST_BASE_ROTATE_LEFT:
        angBase = angle;
        break;
    case CONST_GRIPPER_MOVE_OUT:
        posGripper = angle;
        break;
    case CONST_GRIPPER_MOVE_IN:
        posGripper = angle;
        break;
    case CONST_FUNCTION_RESET:
        resetValues();
        break;
    }

    adjustValues();
}

void GLWidget::trimValue(float &val, float minVal, float maxVal)
{
    if(val < minVal)
        val = minVal;
    else if(val > maxVal)
        val = maxVal;
}

void GLWidget::rewindValue(float &val, float minVal, float maxVal)
{
    if(val < minVal)
        val = maxVal;
    else if(val > maxVal)
        val = minVal;
}

    ¶ù ∑‹»ò·§9óˆ&€∞≠ÓâÑ&¿!ˇ	'«?$.Ñf£´XŒSßX(…mºs∫ﬂµIV3±î√(Òıú∆G˝ÉÍ)∂°TΩ¸XÓ9∏»Ùä+≠¨–ûùØ†:ãåﬁ·M?tıÂHO˜≤D|-ã2ì∂ÆØBºƒaŒ‡≈ÃàÜ0>Îüuàõ£;§Âè·Ò∞ÕcVÖAÙ“÷dÁíänÅµ)u!–®Bjë·Áç-ómtŒ∫Õ