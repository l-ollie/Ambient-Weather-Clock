//**** Using a Teensy 3.2 to Connect an ESP8266 to PC USB Serial *******
//**** Teensy 3.2 RX1 = PIN0 TX1 = PIN1 to ESP8266-01*******
//**** PIN2 to CHPD on ESP8266-01*******

#include "ESPCommunicationFunctions.h"

void setup() {

  // Setup computer to Teensy serial
  Serial.begin(115200);

  // Setup Teensy to ESP8266 serial
  Serial1.begin(115200);

  //Define esp CHPD pin
  pinMode(espChipPowerDown, OUTPUT);
  //Turn esp ON (functions normal)
      restartESP();

}

void loop() {


  //Enable only this to talk directly to ESP through the Serial monitor
  //  serialBrigde();
  //listen to "CONNECT" on the esp
  serialBrigde();

}

