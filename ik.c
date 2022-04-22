#include "inc/ik.h"

static const float l1 = 0.1247;
static const float l2 = 0.1147;
static const float l3 = 0.09498;
static const float l1_2 = 0.01555009;
static const float l2_2 = 0.01315609;
static const float l3_2 = 0.0090212;

float Q_rsqrt( float number )
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;                       // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//  y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}

void init_inv_kin() {
    x = -0.231;
    y = -0.0107;
    z = 0.301;
    th = -M_PI / 4;
    memset(ang,0,sizeof(uint8_t) * SERVO_CNT);
}

void inv_kin() {
   float x_2 = pow(x,2);
   float y_2 = pow(x,2);
   float p = sqrt(x_2 + y_2 + pow(z,2));
   float phi = atan(sqrt(x_2 + y_2) / z);
   float x_c = (p * sin(phi)) - l3 * cos(th);
   float y_c = (p * cos(phi)) - l3 * sin(th);
   int xy_inv = Q_rsqrt(x_2 + y_2);
   ang[0] = atan(y/x);
   ang[1] = atan2(xy_inv * -y_c, xy_inv * -x_c) +
        acos((x_2 + y_2 + l1_2 - l2_2) * 0.5 * 1/l1 * xy_inv);
   ang[2] = atan2((y_c - l1 * sin(ang[1])) / l2, (x_c - l1 * cos(ang[1])) / l2) - ang[1];
   ang[4] = th - (ang[1] + ang[2]);
}
