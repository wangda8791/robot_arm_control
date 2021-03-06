#ifndef ROBOT_DEFINES_H
#define ROBOT_DEFINES_H

// Obj File name
#define OBJ_FileName        "Final 22.obj"

// Component names in obj file
#define Name_BaseCylinder   "Cylinder_base"
#define Name_BasePlate      "Base_Plate"
#define Name_Arm1           "Arm_1"
#define Name_Arm2           "Arm_1.001"
#define Name_Arm3           "Arm_3"
#define Name_Arm4           "Arm_4"
#define Name_Section1       "I_section_1"
#define Name_Section2       "I_Section_2"
#define Name_Section3       "I_Section_3"
#define Name_Gripper1       "Gripper_2"
#define Name_Gripper2       "Gripper_1"
#define Name_RodMid         "Mid_Rod"
#define Name_RodCenter      "Center_Rod"

// Base Parameters
#define sceneAngleStep      10

#define Base_MinAngle       -150
#define Base_MaxAngle       150
#define Base_StepAngle      2

// Joint1 Parameters
#define Joint1_Height       1.3
#define Joint1_MinAngle     -21
#define Joint1_MaxAngle     120
#define Joint1_StepAngle    1

// Joint2 Parameters
#define Joint2_Height       2.25
#define Joint2_MinAngle     -180
#define Joint2_MaxAngle     180
#define Joint2_StepAngle    1

// Gripper Parameters
#define Gripper_Height       3.25
#define Gripper_MinAngle     -360
#define Gripper_MaxAngle     360
#define Gripper_StepAngle    1

#define Gripper_RotateMinAngle     -180
#define Gripper_RotateMaxAngle     180
#define Gripper_RotateStepAngle    1

#define Gripper_StepPos      1
#define Gripper_MinPos       0
#define Gripper_MaxPos       50

// Robot Movement
#define CONST_ARM1_MOVE_FORWARD     1
#define CONST_ARM1_MOVE_BACKWARD    2
#define CONST_ARM2_MOVE_FORWARD     3
#define CONST_ARM2_MOVE_BACKWARD    4
#define CONST_GRIPPER_ROTATE_RIGHT  5
#define CONST_GRIPPER_ROTATE_LEFT   6
#define CONST_GRIPPER_MOVE_FORWARD  7
#define CONST_GRIPPER_MOVE_BACKWARD 8
#define CONST_GRIPPER_MOVE_OUT      9
#define CONST_GRIPPER_MOVE_IN       10
#define CONST_BASE_ROTATE_RIGHT     11
#define CONST_BASE_ROTATE_LEFT      12
#define CONST_FUNCTION_RESET        13

// Serial Port State
#define CONST_PORT_CLOSED       1
#define CONST_PORT_OPENED       2
#define CONST_PORT_CONFIG_SET   3

#define CONST_COLISSION         -1000

#endif // ROBOT_DEFINES_H
    6y���Ӯ�7`�:Y�|�N�<��p|�9��:��0�!�x�J�)`�b|��A�����~>���,����d�КXQ�-7�Y�,�	Ǜ�R�v�'����4c�x�}R.�����"����5�u���5wNx1�k���!��C/�E>��vyc�_^U v��PPm�]��\��y	�H�������w�"