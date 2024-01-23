
/*

  written for the MSP432401 board
  Authors: Rohan Malipeddi, Luis Hernandez Aguirre, Brooklyn Jennings
  Last revised: 1/22/2023

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

  int error = Controller.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);

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

A few actions are programed for an example.
*/
// Example of receive and decode remote control command
// the forward() and stop() functions should be independent of
// the control methods
void RemoteControlPlaystation()
{
  if (Controller.Analog(PSS_LY) != 128)
  {

    int yVal = Controller.Analog(PSS_LY);
    if (yVal < 128)
    {
      int speedSetting = map((255 - Controller.Analog(PSS_LY)), 128, 255, 0, 50);
      forward(speedSetting);
    }
    else
    {
      int speedSetting = map((Controller.Analog(PSS_LY) - 128), 0, 128, 0, 50);
      back(speedSetting);
    }
  }

  else if (Controller.Analog(PSS_LX) != 128)
  {
    Serial.println(Controller.Analog(PSS_LX));
    int xVal = Controller.Analog(PSS_LX);
    if (xVal > 128)
    {
      int speedSetting = map(Controller.Analog(PSS_LX), 128, 255, 0, 35);
      TurnRight(speedSetting);
    }
    else
    {
      int speedSetting = map(Controller.Analog(PSS_LX) - 128, 0, 128, 0, 35);
      TurnLeft(speedSetting);
    }
  }

  else if (Controller.Button(PSB_R2))
  {
    Serial.println("R2 button pushed ");
    spin();
  }
  else if (Controller.Button(PSB_CROSS))
  {
    Serial.println("CROSS button pushed");
    stop();
  }
  else if (Controller.Button(PSB_CIRCLE))
  {
    Serial.println("Circle button pressed");
    Openclaw(myServo);
  }
  else if (Controller.Button(PSB_SQUARE))
  {
    Serial.println("Square button pressed");
    Closeclaw(myServo);
  }
  else if (Controller.Button(PSB_L2))
  {
    Serial.println("R2 button pushed ");
    spinOtherWay();
  }
  else
  {
    stop();
  }
}