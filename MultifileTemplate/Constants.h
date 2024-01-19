const int btBaud = 9600;
const int usbBaud = 57600;

const int PS2_DAT 14;  //P1.7 <-> brown wire
const int PS2_CMD 15;  //P1.6 <-> orange wire
const int PS2_SEL 34;  //P2.3 <-> yellow wire (also called attention)
const int PS2_CLK 35;  //P6.7 <-> blue wire

const int IRrecPin = 33;

const int servoPin = 38;

const float wheelDiameter = 2.7559055; // obtained from example code
const int cntPerRevolution = 360;      // obtained from example code

const int halfJoy = 255 / 2;
const int fullJoy = 255;
const int offJoy = 0;
const int IRrecPin = 33;
const int remoteMap[7][3]{{69, 70, 71},
                          {68, 64, 67},
                          {7, 21, 9},
                          {22, 25, 13},
                          {12, 24, 94},
                          {8, 28, 90},
                          {66, 82, 74}};