/*
Inverse kinematics for the robot


 */ 
#include <string.h>
#include <math.h>
#include "servo.h"

#ifndef __IK_H__
#define __IK_H__

#define AXIS_STEP 1
#define X_MIN -280
#define X_MAX 280

#define Y_MIN 128
#define Y_MAX 230

#define Z_MIN 80
#define Z_MAX 250
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
