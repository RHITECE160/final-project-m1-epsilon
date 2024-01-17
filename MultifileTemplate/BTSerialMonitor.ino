// baud rate: 9600
// name: HC06_Epsilon
// Security Pin 


/* hardware connections 
  state pin         9 (P6.5)
  receiver pin      4 (P3.3)
  tranceiver pin    5 (P3.2)
  en pin            10 (p6.4)
*/


void setup() {
  Serial.begin(57600);
  Serial1.begin(9600);  // use baud rate you set
}

void loop() {
  Serial.println("Using the USB Cable…");
  Serial1.println("Using the Bluetooth Serial...");
  delay(1000);
}
