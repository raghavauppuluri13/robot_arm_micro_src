/*
Inverse kinematics for the robot


 */ 
#include <string.h>
#include <math.h>
#include "servo.h"

#ifndef __IK_H__
#define __IK_H__


float x;
float y;
float z;
float th;

uint8_t ang[SERVO_CNT]; // deg from 0 - 180

void inv_kin();
void init_inv_kin();

#endif
