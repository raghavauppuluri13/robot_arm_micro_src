# robot_arm_micro_src

Source files for robot arm project for ECE 362

[Project Video](https://www.youtube.com/watch?v=FccGxyFGFdw&list=PLnXxGWN1CH0dvdpDsjcVRisxLoUF9EFiQ&index=1)

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
- Place a marker where objects are anticipated to be? (Would have to be input by user)
- If recording motions is added, add a timer to the screen and a red dot to indicate it is being recorded.


Kaden

### Keyboard control

GPIO

Map 6 keyboard keys to +- x/y/z steps 

Anyone, relatively easy
- Kaden is willing to do this as well

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
- A way to record the robot arm's movements and store them for future use.
- Save automatic motions, possibly in an SD card.
- A default reset state for the arm
- Some way of telling the user the controls if advanced functions are added.
- Pick up stacks of boxes and keep it stable.
- Have a continuous move object mode, where when a box is placed on top of a sensor, the arm automatically moves it.
