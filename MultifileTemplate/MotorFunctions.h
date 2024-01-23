/*
  MotorFunctions.ino - Arduino Sketch for Motor Control
  
  Description:
  This sketch provides functions for controlling a RLSK robot, allowing the
  motors to move forward and stop.

  Functions:
  1. void forward()
     - Activates the motor to move forward.
  2. void back() 
     - Activates both motors to move backward
  3. void TurnRight() 
     - Actives left motor on speed specified and other on lowspeed or 0
  4. void TurnLeft() 
     - Actives right motor on speed specified and other on lowspeed or 0
  5. void spin()
     - Actives left motor to go back and right to go front at fastspeed or 30
  5. void spinOtherWay()
     - Actives right motor to go back and left to go front at fastspeed or 30
  6. void OpenClaw()
     - Sets servo motor to 0 degrees
  6. void CloseClaw()
     - Sets servo motor to 180 degrees
  2. void stop()
     - Stops both motors.
  
  Created by: Rohan Malipeddi
  Date: 1/22/24
  Version: 1.0
*/

//included headers files just to be safe
#include <PS2X_lib.h>
#include <Servo.h>
#include "SimpleRSLK.h"

//- Activates the motor to move forward.
void forward(int speed) {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorSpeed(BOTH_MOTORS, speed);
}

//- Activates both motors to move backward
void back(int speed) {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorSpeed(BOTH_MOTORS, speed);
}

//- Actives left motor on speed specified and other on lowspeed or 0
void TurnRight(int speed) {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorSpeed(RIGHT_MOTOR, 0);
  setMotorSpeed(LEFT_MOTOR, speed);
}

//Actives right motor on speed specified and other on lowspeed or 0
void TurnLeft(int speed) {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorSpeed(LEFT_MOTOR, 0);
  setMotorSpeed(RIGHT_MOTOR, speed);
}

//Actives left motor to go back and right to go front at fastspeed or 30
void spin() {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorSpeed(LEFT_MOTOR, 30);
  setMotorSpeed(RIGHT_MOTOR, 30);
}

//Actives right motor to go back and left to go front at fastspeed or 30
void spinOtherWay() {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorSpeed(LEFT_MOTOR, 50);
  setMotorSpeed(RIGHT_MOTOR, 50);
}

//Sets servo motor to 0 degrees
void Openclaw(Servo myServo) {
  //enableMotor(SERVOS_PER_TIMER);
  myServo.write(0);
  delay(100);
}

//Sets servo motor to 180 degrees
void Closeclaw(Servo fServo) {
  //enableMotor(SERVOS_PER_TIMER);
  fServo.write(180);
  delay(100);
}

/* Stops robot forward: both motors disabled */
void stop() {
    disableMotor(BOTH_MOTORS);
}
