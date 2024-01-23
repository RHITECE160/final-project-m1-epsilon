
/*A multifile project code template
  A template for the Milestone 1 project code that uses multiple files
  for modularity. The compiler first loads the principal file
  (the one with the same name as the folder) and then loads
  the others in alphabetical order. Variables defined in an
  earlier file will be visible to code in a file that is loaded
  later, but not vice-versa.

  Calls functions in files:
  MotorFunctions.ino

  written for the MSP432401 board
  Author: Deborah Walter
  Last revised: 11/28/2023

***** Hardware Connections: *****
     start button       P3.0
     playstation connections
     brown wire         P1.7
     orange wire        P1.6
     yellow wire        P2.3
     blue wire          P6.7
*/

// Load libraries used
<<<<<<< HEAD
#include <SimpleRSLK.h>
#include <Servo.h>
#include <PS2X_lib.h>
#include <TinyIRremote.h>
#include "Constants.h"
#include "MotorFunctions.h"
#include "Driving.h"
=======
#include "SimpleRSLK.h"
#include "Servo.h"
#include "PS2X_lib.h"
#include "TinyIRremote.h"
#include "Constants.h"
>>>>>>> d72d1216413e3e46eeeaf1d73be5f509e5fd00cc

// Define remote mode either playstation controller or IR remote controller
enum RemoteMode
{
  PLAYSTATION,
  IR_REMOTE,
};

IRreceiver irx(IRrecPin);
IRData irResults;

PS2X Controller;
Servo myServo;

// Declare and initialize the current state variable
RemoteMode CurrentRemoteMode = PLAYSTATION;
int betterRemoteMode = 0;

// Tuning Parameters
const uint16_t lowSpeed = 15;
const uint16_t fastSpeed = 50;

<<<<<<< HEAD
void setup()
{
  Serial.begin(usbBaud); // plug in terminal
  Serial1.begin(btBaud); // bluetooth terminal (out going com)
=======


void setup() {
  Serial.begin(usbBaud); // plug in terminal 
  Serial1.begin(btBaud);  // bluetooth terminal (out going com) 
>>>>>>> d72d1216413e3e46eeeaf1d73be5f509e5fd00cc
  Serial.println("Using the USB Cable…");
  Serial1.println("Using the Bluetooth Serial...");

  // Run setup code
  setupRSLK();
<<<<<<< HEAD
  myServo.attach(servoPin);

  if (CurrentRemoteMode == 0)
  {
=======
  myServo.attach(servoPin); 


  if (CurrentRemoteMode == 0) {
>>>>>>> d72d1216413e3e46eeeaf1d73be5f509e5fd00cc
    // using the playstation controller
    Serial.println("Using playstation controller, make sure it is paired first ");

    // Initialize PlayStation controller
    delayMicroseconds(500 * 1000); // added delay to give wireless ps2 module some time to startup, before configuring it
    // declare variables for playstation control
<<<<<<< HEAD
  }
  else if (CurrentRemoteMode == 1)
  {
=======
    int error = 1;

    while (error) {
      error = Controller.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);

      if (error == 0)
        Serial.println("Found Controller, configured successful ");

      else if (error == 1)
        Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

      else if (error == 2)
        Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

      else if (error == 3)
        Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
      delayMicroseconds(1000 * 1000);
    }
  } else if (CurrentRemoteMode == 1) {
>>>>>>> d72d1216413e3e46eeeaf1d73be5f509e5fd00cc
    // put start-up code for IR controller here if neccessary
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
  delayMicroseconds(1000 * 1000);

  if (irx.initIRReceiver())
  {
    Serial.println("IR Receiver Works");
    enableRXLEDFeedback(LED_BUILTIN);
  }
  else
  {
    Serial.println("IR Receiver Busted");
  }
}

void loop()
{
  // Read input from PlayStation controller
  Controller.read_gamepad();
<<<<<<< HEAD
  enableMotor(BOTH_MOTORS);
=======
>>>>>>> d72d1216413e3e46eeeaf1d73be5f509e5fd00cc

  switch (betterRemoteMode)
  {

  case 0:
    if (Controller.Button(PSB_L1))
    {
      driveByController(Controller, myServo);
    }
    if (Controller.Button(PSB_SELECT))
    {
      betterRemoteMode = 1;
      Serial.print("Control Mode : ");
      Serial.println(betterRemoteMode);
      delay(40);
    }
    else
    {
      Serial.println("Controller Selected");
    }

    break;

  case 1:
    driveByRemote(irx, irResults, myServo);
    if (Controller.Button(PSB_START))
    {
      betterRemoteMode = 0;
      Serial.print("Control Mode : ");
      Serial.println(betterRemoteMode);
      delay(40);
    }
    else
    {
      Serial.println("IR Remote Selected");
    }
    break;
  }
  // Operate the robot in remote control mode
}

/* RemoteControlPlaystation() function
This function uses a playstation controller and the PLSK libraray with
an RLSK robot using to implement remote controller.

A few actions are programed for an example.

Button control map:
PAD UP button moves both motors forward
CROSS button stops motors
*/

<<<<<<< HEAD
/*
void RemoteControlPlaystation() {
   // put your code here to run in remote control mode
=======
    // Example of receive and decode remote control command
    // the forward() and stop() functions should be independent of
    // the control methods
    if (Controller.Button(PSB_PAD_UP)) {
      Serial.print(Controller.Button(PSB_PAD_UP));
      Serial.println("PAD UP button pushed ");
      forward();
    } 
    else if(Controller.Button(PSB_PAD_DOWN)) {
      Serial.println("PAD DOWN button pushed ");
      back();
    }
    else if(Controller.Button(PSB_PAD_RIGHT)) {
      Serial.println("PAD RIGHT button pushed ");
      TurnRight();
    }
    else if(Controller.Button(PSB_PAD_LEFT)) {
      Serial.println("PAD LEFT button pushed ");
      TurnLeft();
    }
    else if(Controller.Button(PSB_R2)) {
      Serial.println("R2 button pushed ");
      spin();
    }
    else if (Controller.Button(PSB_CROSS)) {
      Serial.println("CROSS button pushed");
      stop();
    } 
    else if(Controller.Button(PSB_CIRCLE)) {
      Serial.println("Circle button pressed");
      Openclaw(myServo);
    } 
    else if(Controller.Button(PSB_SQUARE)) {
      Serial.println("Square button pressed");
      Closeclaw(myServo);
    }
    else {
      stop();
    }
>>>>>>> d72d1216413e3e46eeeaf1d73be5f509e5fd00cc

   // Example of receive and decode remote control command
   // the forward() and stop() functions should be independent of
   // the control methods
   if (Controller.Button(PSB_PAD_UP)) {
     Serial.print(Controller.Button(PSB_PAD_UP));
     Serial.println("PAD UP button pushed ");
     forward();
   }
   else if(Controller.Button(PSB_PAD_DOWN)) {
     Serial.println("PAD DOWN button pushed ");
     back();
   }
   else if(Controller.Button(PSB_PAD_RIGHT)) {
     Serial.println("PAD RIGHT button pushed ");
     TurnRight();
   }
   else if(Controller.Button(PSB_PAD_LEFT)) {
     Serial.println("PAD LEFT button pushed ");
     TurnLeft();
   }
   else if(Controller.Button(PSB_R2)) {
     Serial.println("R2 button pushed ");
     spin();
   }
   else if (Controller.Button(PSB_CROSS)) {
     Serial.println("CROSS button pushed");
     stop();
   }
   else if(Controller.Button(PSB_CIRCLE)) {
     Serial.println("Circle button pressed");
     Openclaw(myServo);
   }
   else if(Controller.Button(PSB_SQUARE)) {
     Serial.println("Square button pressed");
     Closeclaw(myServo);
   }
   else {
     stop();
   }

 }
 */
