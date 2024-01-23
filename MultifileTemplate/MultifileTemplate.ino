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
#include "SimpleRSLK.h"
#include <Servo.h>
#include "PS2X_lib.h"

// Define pin numbers for the button on the PlayStation controller
#define PS2_DAT 14  //P1.7 <-> brown wire
#define PS2_CMD 15  //P1.6 <-> orange wire
#define PS2_SEL 34  //P2.3 <-> yellow wire (also called attention)
#define PS2_CLK 35  //P6.7 <-> blue wire


// Create an instance of the playstation controller object
PS2X ps2x;

// Define remote mode either playstation controller or IR remote controller
enum RemoteMode {
  PLAYSTATION,
  IR_REMOTE,
};

// Declare and initialize the current state variable
RemoteMode CurrentRemoteMode = PLAYSTATION;
//RemoteMode CurrentRemoteMode = IR_REMOTE;

// Tuning Parameters
const uint16_t lowSpeed = 15;
const uint16_t fastSpeed = 50;

const int servoPin = 38;
Servo myServo;


void setup() {
  Serial.begin(57600);
  Serial.print("Starting up Robot code...... Hello World");

  // Run setup code
  setupRSLK();

  //setup esrvo
  myServo.attach(servoPin); 

  if (CurrentRemoteMode == 0) {
    // using the playstation controller
    Serial.println("Using playstation controller, make sure it is paired first ");

    // Initialize PlayStation controller
    delayMicroseconds(500 * 1000);  //added delay to give wireless ps2 module some time to startup, before configuring it
    // declare variables for playstation control
    bool pressures = false;
    bool rumble = false;
    int error = 1;

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
      delayMicroseconds(1000 * 1000);
    }
  } else if (CurrentRemoteMode == 1) {
    // put start-up code for IR controller here if neccessary

  }
}

void loop() {
  // Read input from PlayStation controller
  ps2x.read_gamepad();

  // Operate the robot in remote control mode
  if (CurrentRemoteMode == 0) {
    Serial.println("Running remote control with the Playstation Controller");
    RemoteControlPlaystation();

  } else if (CurrentRemoteMode == 1) {
    // put code here to run using the IR controller if neccessary

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
  void RemoteControlPlaystation() {
    // put your code here to run in remote control mode

    // Example of receive and decode remote control command
    // the forward() and stop() functions should be independent of
    // the control methods

    if (ps2x.Analog(PSS_LY) != 128) {
      //int speedSetting = map(ps2x.Analog(PSS_LY), 128, 255, 0, 50);
      //Serial.println(ps2x.Analog(PSS_LY));
      int yVal = ps2x.Analog(PSS_LY);
      if(yVal < 128) {
        int speedSetting = map((255-ps2x.Analog(PSS_LY)), 128, 255, 0, 50);
        forward(speedSetting);
      }
      else {
        int speedSetting = map((ps2x.Analog(PSS_LY)-128), 0, 128, 0, 50);
        back(speedSetting);
      }
      //int speedSetting = map((255-ps2x.Analog(PSS_LY)), 128, 255, 0, 50);
      //Serial.println(speedSetting);
      //Serial.println("PAD UP button pushed ");
      //forward(speedSetting);
      //driveByController(ps2x.Analog(PSS_LY));
    } 
    // else if(ps2x.Button(PSB_R1)) {
    //   //Serial.println(ps2x.Analog(PSS_LY));
    //   int speedSetting = map((ps2x.Analog(PSS_LY)-128), 0, 128, 0, 50);
    //   //int speedSetting = map(ps2x.Analog(PSS_LY), 128, 0, 0, 50);
    //   //Serial.println(speedSetting);
    //   //Serial.println("PAD DOWN button pushed ");
    //   back(speedSetting);
    //   //driveByController(ps2x.Analog(PSS_LY));
    // }
    else if(ps2x.Analog(PSS_LX) != 128) {
      //Serial.println("PAD RIGHT button pushed ");
      Serial.println(ps2x.Analog(PSS_LX));
      int xVal = ps2x.Analog(PSS_LX);
      if(xVal > 128) {
        int speedSetting = map(ps2x.Analog(PSS_LX), 128, 255, 0, 35);
        TurnRight(speedSetting);
      }
      else {
        int speedSetting = map(ps2x.Analog(PSS_LX), 0, 128, 0, 35);
        TurnLeft(speedSetting);
      }
      //TurnRight();
    }
    // else if(ps2x.Button(PSB_PAD_LEFT)) {
    //   Serial.println("PAD LEFT button pushed ");
    //   TurnLeft();
    // }
    else if(ps2x.Button(PSB_R2)) {
      Serial.println("R2 button pushed ");
      spin();
    }
    else if (ps2x.Button(PSB_CROSS)) {
      Serial.println("CROSS button pushed");
      stop();
    } 
    else if(ps2x.Button(PSB_CIRCLE)) {
      Serial.println("Circle button pressed");
      Openclaw(myServo);
    } 
    else if(ps2x.Button(PSB_SQUARE)) {
      Serial.println("Square button pressed");
      Closeclaw(myServo);
    }
    else if(ps2x.Button(PSB_L2)) {
      Serial.println("R2 button pushed ");
      spinOtherWay();
    }
    else {
      stop();
    }

  }
