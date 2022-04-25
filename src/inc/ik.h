/*
Inverse kinematics for the robot
 */
#include <string.h>
#include <math.h>
#include "servo.h"

#ifndef __IK_H__
#define __IK_H__

#define AXIS_STEP 2
#define X_MIN -280
#define X_MAX 280

#define Y_MIN 160
#define Y_MAX 230

#define Z_MIN 60
#define Z_MAX 230
#define GRIP_MIN 5
#define GRIP_MAX 45

float x;
float y;
float z;
float th;
float grip;

float ang[SERVO_CNT]; // deg from 0 - 180

void inv_kin();
void init_inv_kin();

#endif
