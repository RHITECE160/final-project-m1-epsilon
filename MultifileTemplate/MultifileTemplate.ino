/*
  name: Milestone 1 both Controller full functionality code
  Description: This code enables the robot to understand commands from the robot and executes them.
  written for the MSP432401 board
  Authors: Rohan Malipeddi, Luis Hernandez Aguirre, Brooklyn Jennings
  Last revised: 1/22/2023

  Hardware Connections: 
  In Constants.h

  Main functions: 
  1. RemoteControlPlayStation() 
      - contains mapping of playstation buttons to functions used in MotorFunction.h

  2. driveByRemote() 
      - used in the loop under case 1, to call driveByRemote() function in Driving.h

  Main variables:
  PLAYSTATION -> used to select playstation controller
  betterRemoteMode -> used to select between the two controllers
  irResults -> displays IR results 
  irx(IRrecPin) 
  Controller ->PS2X object that interprets the playstation controller
  myServo -> servo object to manipulate servo
  
*/

// Load libraries used
#include <SimpleRSLK.h>
#include <Servo.h>
#include <PS2X_lib.h>
#include <TinyIRremote.h>

#include "Constants.h"
#include "MotorFunctions.h"
#include "Driving.h"

PS2X Controller;
Servo myServo;

// Declare and initialize the current state variable
int controlMode = 1;

// Tuning Parameters
const uint16_t lowSpeed = 15;
const uint16_t fastSpeed = 50;

void setup()
{
  Serial.begin(usbBaud); // plug in terminal
  Serial1.begin(btBaud); // bluetooth terminal (out going com)
  Serial.println("Using the USB Cable…");
  Serial1.println("Using the Bluetooth Serial...");

  // Run setup code
  setupRSLK();
  myServo.attach(servoPin);

  if (controlMode == 0)
  {
    // using the playstation controller
    Serial.println("Starting with playstation controller, make sure it is paired first ");

    // Initialize PlayStation controller
    delay(50); // added delay to give wireless ps2 module some time to startup, before configuring it
    // declare variables for playstation control
  }
  else if (controlMode == 1)
  {
    // put autonomous initialization code for here if neccessary
    Serial.println("Starting in Autonomous")
  }


    while (error) {
      error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

      if (error == 0)
        Serial.println("Found Controller, configured successful ");

      else if (error == 1)
        Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

      else if (error == 2)
        Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

      else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  delay(50);


}

void loop()
{
  // Read input from PlayStation controller
  Controller.read_gamepad();
  enableMotor(BOTH_MOTORS);

  // Starts by default with betterRemoteMode as 0, this is the playstation mode, when you hit the Select button it
  // switches over to IR control, when in IR control mode when the start button is pressed it will switch back to the controller.
  switch (controlMode)
  {
  // Controller mode, when L1 is pressed it drives according to the driveByController function
  case 0:
    // replace THIS CODE WITH YOUR CONTROLLER DRIVING CODE
    RemoteControlPlaystation();
    if (Controller.Button(PSB_SELECT))
    {
      controlMode = 1;
      Serial.println("Control Mode : Autonomous");
      delay(40);
    }
    else
    {
      Serial.println("Controller Selected");
    }

    break;

    // Autonomous, calls drive by remote repeatedly until start button is pressed
  case 1:
    if (Controller.Button(PSB_START))
    {
      controlMode = 0;
      Serial.println("Control Mode : Manual");
      delay(40);
    }
    else
    {
      Serial.println("Autonomous Selected");
    }
    break;
  }
}

/* RemoteControlPlaystation() function
This function uses a playstation controller and the PLSK libraray with
an RLSK robot using to implement remote controller.
*/
void RemoteControlPlaystation(){
    //checks if the joystick is moved
    if (Controller.Analog(PSS_LY) != 128) {
      //assigning a value for y position of the joystick
      int yVal = Controller.Analog(PSS_LY);
      //the joystick becomes less as I move it forward, so condition is opposite
      if(yVal < 128) {  
        //mapped to specific speeds
        int speedSetting = map((255-Controller.Analog(PSS_LY)), 128, 255, 0, 50);
        forward(speedSetting);
      }
      else {
        //mapped to specific speeds
        int speedSetting = map((Controller.Analog(PSS_LY)-128), 0, 128, 0, 50);
        back(speedSetting);
      }

    } 
    //joystick moved?
    else if(Controller.Analog(PSS_LX) != 128) {
      //assigning a value for x position of the joystick
      int xVal = Controller.Analog(PSS_LX);
      //horizontal motoin moves like normal
      if(xVal > 128) {
        //mapped to specific speeds
        int speedSetting = map(Controller.Analog(PSS_LX), 128, 255, 0, 35);
        TurnRight(speedSetting);
      }
      else {
        //mapped to specific speeds
        int speedSetting = map((Controller.Analog(PSS_LX)-128), 0, 128, 0, 35);
        TurnLeft(speedSetting);
      }
    }

    //spin mapping
    else if(Controller.Button(PSB_R2)) {
      Serial.println("R2 button pushed ");
      spin();
    }
    //force stop mapping
    else if (Controller.Button(PSB_CROSS)) {
      Serial.println("CROSS button pushed");
      stop();
    } 
    //claw open map
    else if(Controller.Button(PSB_CIRCLE)) {
      Serial.println("Circle button pressed");
      Openclaw(myServo);
    } 
    //claw close map
    else if(Controller.Button(PSB_SQUARE)) {
      Serial.println("Square button pressed");
      Closeclaw(myServo);
    }
    //spin other way map
    else if(Controller.Button(PSB_L2)) {
      Serial.println("R2 button pushed ");
      spinOtherWay();
    }
    //default stop if nothing pressed
    else {
      stop();
    }
} //end RemoteControlPlaystation
