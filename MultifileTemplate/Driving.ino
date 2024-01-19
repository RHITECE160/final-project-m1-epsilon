#include "TinyIRremote.h"
#include "Servo.h"
#include "Sensors.h"
#include "SimpleRSLK.h"
#include "MotorFunctions.ino"


void driveByRemote()
{
    int state = 0;
    irx.decodeIR(&irResults);
    state = irResults.command;
    
    
    switch (state)
    {
    case 90:
        // spin right
        driveByDirection(0,30);
        break;

    case 94:
        // curve forward right
        driveByDirection(45,30);
        break;

    case 24:
        // drive forwards
        driveByDirection(90, 30);
        break;

    case 12:
        // curve forward left
        driveByDirection(135, 30);
        break;

    case 8:
        // spin left
        driveByDirection(180,30);
        break;

    case 66:
        // curve back left
        driveByDirection(225,30);
        break;

    case 82:
        // backwards
        driveByDirection(270,30);
        break;

    case 74:
        // curve back right
        driveByDirection(315,30);
        break;
    default:
    Serial.println("no direction selected");
    setMotorSpeed(BOTH_MOTORS,0);
    delay(100);
    break;
    }
    switch (state)
    {
        case 70:
        myServo.write(180);
        delay(40);
        break;
        case 21:
        myServo.write(0);
        delay(40);
        break;
    }
    


}

// direction is an int that is in 45 degree increments with 0 equal to right
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
    Serial.print("direction: ");
    Serial.print(direction);
    Serial.print(", Speed: ");
    Serial.println(speed);
    delay(100);
}
void driveByController(){
    int rawJoyLY = Controller.Analog(PSS_LY);
    int moveSpeed = 0;

    Serial.print("Joystick Raw Value: ");
    Serial.println(rawJoyLY);
    enableMotor(BOTH_MOTORS);

    if(rawJoyLY <= 255/2){
        setMotorDirection(BOTH_MOTORS,MOTOR_DIR_BACKWARD);
        moveSpeed = map(255-rawJoyLY,offJoy,halfJoy,0,20);
    }
    else{
        setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);
        moveSpeed = map(rawJoyLY,halfJoy,fullJoy,0,20);
    }

    setMotorSpeed(BOTH_MOTORS, moveSpeed);
    Serial.print("Motor adjusted value: ");
    Serial.println(moveSpeed);
}
