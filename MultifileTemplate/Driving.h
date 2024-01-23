#include "TinyIRremote.h"
#include "Servo.h"
#include "SimpleRSLK.h"
#include "PS2X_lib.h"

int halfJoy = 255 / 2;
int fullJoy = 255;
int offJoy = 0;

// direction is an int that is in 45 degree increments with 0 equal to right
// takes in angles and drives in directions corresponding to the inputs at the set speed
void driveByDirection(int direction, int speed)
{
    enableMotor(BOTH_MOTORS);
    switch (direction)
    {
    case 0:
        setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
        setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
        setMotorSpeed(BOTH_MOTORS, speed);
        break;
    case 45:
        setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD);
        setMotorSpeed(RIGHT_MOTOR, speed / 2);
        setMotorSpeed(LEFT_MOTOR, speed);
        break;
    case 90:
        setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD);
        setMotorSpeed(BOTH_MOTORS, speed);
        break;
    case 135:
        setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD);
        setMotorSpeed(RIGHT_MOTOR, speed);
        setMotorSpeed(LEFT_MOTOR, speed / 2);
        break;
    case 180:
        setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
        setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
        setMotorSpeed(BOTH_MOTORS, speed);
        break;
    case 225:
        setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
        setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
        setMotorSpeed(RIGHT_MOTOR, speed);
        setMotorSpeed(LEFT_MOTOR, speed / 2);
        break;
    case 270:
        setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
        setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
        setMotorSpeed(BOTH_MOTORS, speed);
        break;
    case 315:
        setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
        setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
        setMotorSpeed(RIGHT_MOTOR, speed / 2);
        setMotorSpeed(LEFT_MOTOR, speed);
        break;
    default:
        break;
    }
    Serial.print("Remote Direction: ");
    Serial.print(direction);
    Serial.print(", Speed: ");
    Serial.println(speed);
    delay(100);
}

/*
function that takes IR objects and can perform all needed movements for checkpoint one by 
setting the servo or by calling the  driveByDirection function*/
void driveByRemote(IRreceiver fIRx, IRData fIRResults, Servo fServo)
{
    int state = 0;
    fIRx.decodeIR(&fIRResults);
    state = fIRResults.command;

    switch (state)
    {
    case 90:
        // spin right
        driveByDirection(0, 10);
        break;

    case 94:
        // curve forward right
        driveByDirection(45, 10);
        break;

    case 24:
        // drive forwards
        driveByDirection(90, 10);
        break;

    case 12:
        // curve forward left
        driveByDirection(135, 10);
        break;

    case 8:
        // spin left
        driveByDirection(180, 10);
        break;

    case 66:
        // curve back left
        driveByDirection(225, 10);
        break;

    case 82:
        // backwards
        driveByDirection(270, 10);
        break;

    case 74:
        // curve back right
        driveByDirection(315, 10);
        break;
    default:
        Serial.print("No direction selectedl, IR cmd: ");
        Serial.println(fIRResults.command);
        setMotorSpeed(BOTH_MOTORS, 0);
        delay(300);
        break;
    }
    switch (state)
    {
    case 70:
        fServo.write(180);
        delay(40);
        break;
    case 21:
        fServo.write(0);
        delay(40);
        break;
    }
}
// This function takes in the controller and servo objects and sets the joystick relative to the centerpoint
// it implements a deadzone when the motor power would be less than 5%
void driveByController(PS2X fController, Servo fServo)
{
    int rawJoyLY = fController.Analog(PSS_LY);
    int moveSpeed = 0;

    Serial.print("Joystick Raw Value: ");
    Serial.println(rawJoyLY);
    enableMotor(BOTH_MOTORS);

    if (rawJoyLY <= 255 / 2)
    {
        setMotorDirection(BOTH_MOTORS, MOTOR_DIR_BACKWARD);
        moveSpeed = map(255 - rawJoyLY, offJoy, halfJoy, 0, 20);
    }
    else
    {
        setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD);
        moveSpeed = map(rawJoyLY, halfJoy, fullJoy, 0, 20);
    }
    if (moveSpeed < 5)
    {
        moveSpeed = 0;
    }
    setMotorSpeed(BOTH_MOTORS, moveSpeed);
    Serial.print("Motor adjusted value: ");
    Serial.println(moveSpeed);
    delay(50);
}
