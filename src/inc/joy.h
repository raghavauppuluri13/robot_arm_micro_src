#ifndef __JOY_H__
#define __JOY_H__
#include "stm32f0xx.h"

#define BCSIZE 32
#define JOY_CNT 6
#define UPPER_JOY_MID 2300
#define LOWER_JOY_MID 1500

/*
  - Data Pinouts:
    - 2 Joysticks (one axis will be unused):
        - X-axis, PC0, ADC_IN10, JOY ID 0
        - Y-axis, PC1, ADC_IN11, JOY ID 1
        - Z-axis, PC2, ADC_IN12, JOY ID 2
    - 3 Potentiometers (10kohm pots):
        - Wrist-roll, PC3, ADC_IN13, JOY ID 3
        - Wrist-pitch, PC4, ADC_IN14, JOY ID 4
        - Gripper, PC5, ADC_IN15, JOY ID 5
 */

struct JoySpec {
    // GPIOC
    uint8_t pin;
    // channel
    uint8_t ch;
};

static const struct JoySpec joy_specs[JOY_CNT] = {
  { .pin = 0, .ch = 10},
  { .pin = 1, .ch = 11},
  { .pin = 2, .ch = 12},
  { .pin = 3, .ch = 13},
  { .pin = 4, .ch = 14},
  { .pin = 5, .ch = 15}
};

struct Joy {
    // output of boxcar value
    int32_t val;
    // boxcar averaging
    int bcsum;
    int boxcar[BCSIZE];
    int bcn;
};


void init_joys();
void start_joys(void);
void init_tim15();

#endif
