# robot_arm_micro_src

Source files for robot arm project for ECE 362

## Arm Details

- 6 Hobby servos controlled with PWM (duty cycle corresponds to angle)
- [Servo 0-2 datasheet](https://components101.com/sites/default/files/component_datasheet/MG996R-Datasheet.pdf)
- [Servo 3 datasheet](http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf)
- [Servo 4-5](https://www.agf-rc.com/agfrc-digital-servo-b11dls-p1670802.html)

## System Overview

### Servo Comms

PWM/Timers/ADC

- Angle to PWM interface -> use Timers and DAC

Raghava

### LCD Display

- X, Y, Z Coordinates
- Top down view and side view
- Current state?


Kaden

### Keyboard control

GPIO

Map 6 keyboard keys to +- x/y/z steps 

Anyone, relatively easy
Kaden is willing to do this as well

### Robot Stuff

Convert current position of gripper to joint angles (inverse kinematics). Need to use fixed point math. 

Raghava/Rohan

### Circuit Design

- Connect all servos in parallel to 5V/ground
- Connect servo data pins to respective STM32 pinouts

Rohit/Kaden

### Safety

- Establish joint limits and operating range, draw circle.
- Wired E-stop connected to circuit to cut power

### Other Random Ideas/Notes if needed
- Automatic Advanced controls by way of keypad
- Extend the base to be the extent of the safety circle
- Save automatic motions, possibly in an SD card.
- A default reset state for the arm
- Some way of telling the user the controls if advanced functions are added.
