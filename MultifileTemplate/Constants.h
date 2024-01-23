/*
***** Hardware Connections: *****
    start button       P3.0
    playstation connections
    brown wire         P1.7 
    orange wire        P1.6 
    yellow wire        P2.3
    blue wire          P6.7
    IRrecPin           33
    servoPin           38
    remoteMap          
*/
 
//chosen baud rate for each Serial port
 int btBaud = 9600;
 int usbBaud = 57600;

 int PS2_DAT = 14;  //P1.7 <-> brown wire
 int PS2_CMD = 15;  //P1.6 <-> orange wire;
 int PS2_SEL = 34;  //P2.3 <-> yellow wire (also called attention);
 int PS2_CLK = 35;  //P6.7 <-> blue wire

 int IRrecPin = 33;

 int servoPin = 38;
 float wheelDiameter = 2.7559055; // obtained from example code, wheel diameter for driving in auto
 int cntPerRevolution = 360;      // obtained from example code, wheel encoder resolution

 int remoteMap[7][3]{     {69, 70, 71},  //mapping of remote inputs
                          {68, 64, 67},
                          {7, 21, 9},
                          {22, 25, 13},
                          {12, 24, 94},
                          {8, 28, 90},
                          {66, 82, 74}};
        
