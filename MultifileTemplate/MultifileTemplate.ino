
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

void setup()
{
  Serial.begin(usbBaud); // plug in terminal
  Serial1.begin(btBaud); // bluetooth terminal (out going com)
  Serial.println("Using the USB Cable…");
  Serial1.println("Using the Bluetooth Serial...");

  // Run setup code
  setupRSLK();
  myServo.attach(servoPin);

  if (CurrentRemoteMode == 0)
  {
    // using the playstation controller
    Serial.println("Using playstation controller, make sure it is paired first ");

    // Initialize PlayStation controller
    delayMicroseconds(500 * 1000); // added delay to give wireless ps2 module some time to startup, before configuring it
    // declare variables for playstation control
  }
  else if (CurrentRemoteMode == 1)
  {
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
  enableMotor(BOTH_MOTORS);

//Starts by default with betterRemoteMode as 0, this is the playstation mode, when you hit the Select button it
//switches over to IR control, when in IR control mode when the start button is pressed it will switch back to the controller.
  switch (betterRemoteMode)
  {
  //Controller mode, when L1 is pressed it drives according to the driveByController function
  case 0:



  // replace THIS CODE WITH YOUR CONTROLLER DRIVING CODE
      driveByController(Controller, myServo);



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

//IR Remote Section, calls drive by remote repeatedly until start button is pressed
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
}

/* RemoteControlPlaystation() function
This function uses a playstation controller and the PLSK libraray with
an RLSK robot using to implement remote controller.

A few actions are programed for an example.

Button control map:
PAD UP button moves both motors forward
CROSS button stops motors
*/

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
