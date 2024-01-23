/*
  MotorFunctions.ino - Arduino Sketch for Motor Control
  
  Description:
  This sketch provides functions for controlling a RLSK robot, allowing the
  motors to move forward and stop.

  Functions:
  1. void moveForward()
     - Activates the motor to move forward.

  2. void stopMotor()
     - Stops the motor.

  Created by: Your Name
  Date: Current Date
  Version: 1.0
*/
#include <PS2X_lib.h>
#include <Servo.h>
#include "SimpleRSLK.h"



/* Moves robot forward: both motors forward same speed */

// const int halfJoy = 255 / 2;
// const int fullJoy = 255;
// const int offJoy = 0;

// void driveByController(int rawJoyLY){
//     //int rawJoyLY = Controller.Analog(PSS_LY);
//     int moveSpeed = 0;

//     //Serial.print("Joystick Raw Value: ");
//     //Serial.println(rawJoyLY);
//     enableMotor(BOTH_MOTORS);

//     if(rawJoyLY <= 255/2){
//         setMotorDirection(BOTH_MOTORS,MOTOR_DIR_BACKWARD);
//         moveSpeed = map(255-rawJoyLY,offJoy,halfJoy,0,20);
//     }
//     else{
//         setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);
//         moveSpeed = map(rawJoyLY,halfJoy,fullJoy,0,20);
//     }

//     setMotorSpeed(BOTH_MOTORS, moveSpeed);
//     //Serial.print("Motor adjusted value: ");
//     //Serial.println(moveSpeed);
// }

void forward(int speed) {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorSpeed(BOTH_MOTORS, speed);
}

void back(int speed) {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorSpeed(BOTH_MOTORS, speed);
}

void TurnRight(int speed) {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorSpeed(RIGHT_MOTOR, 0);
  setMotorSpeed(LEFT_MOTOR, speed);
}

void TurnLeft(int speed) {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorSpeed(LEFT_MOTOR, 0);
  setMotorSpeed(RIGHT_MOTOR, speed);
}

void spin() {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorSpeed(LEFT_MOTOR, 30);
  setMotorSpeed(RIGHT_MOTOR, 30);
}

void spinOtherWay() {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorSpeed(LEFT_MOTOR, 50);
  setMotorSpeed(RIGHT_MOTOR, 50);
}

void Openclaw(Servo myServo) {
  //enableMotor(SERVOS_PER_TIMER);
  myServo.write(0);
  delay(100);
}

void Closeclaw(Servo fServo) {
  //enableMotor(SERVOS_PER_TIMER);
  fServo.write(180);
  delay(100);
}

/* Stops robot forward: both motors disabled */
void stop() {
    disableMotor(BOTH_MOTORS);
}
