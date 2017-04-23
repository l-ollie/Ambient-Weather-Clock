//**** Using a Teensy 3.2 to Connect an ESP8266 to PC USB Serial *******
//**** Teensy 3.2 RX1 = PIN0 TX1 = PIN1 to ESP8266-01*******
//**** Teensy PIN2 to CHPD on ESP8266-01*******

const String password = "f4CS36xVmnjn";
const String ssid = "VGV75190DE816";

const String weatherApi = "api.openweathermap.org";
const String weatherApiCityInNl = "utrecht";
String weatherApiKey = "5930c34e06a21b4ff7ccb6bf9ddb5f3e";


#include "ESPCommunicationFunctions.h"

void setup() {

  // Setup computer to Teensy serial
  Serial.begin(115200);

  // Setup Teensy to ESP8266 serial
  Serial1.begin(115200);

  delay(1000);
  if (startESP()) {
    getWeather();
  }

//  pinMode(2, OUTPUT);
//  digitalWrite(2, HIGH);
}

void loop() {
  //Enable only this to talk directly to ESP through the Serial monitor
  serialBrigde();

}

