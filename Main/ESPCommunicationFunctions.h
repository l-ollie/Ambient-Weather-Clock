#include "ESPCommunicationHandler.h"

//Define esp CHPD pin
const int espChipPowerDown = 2;

//========================================
//========================================   ESP BASICS
//========================================

void shutdownESP() {
  Serial.println("shutdownESP turning off ESP");
  pinMode(espChipPowerDown, OUTPUT);
  digitalWrite(espChipPowerDown, LOW);
  Serial1.flush();
}


//========================================
//========================================   ESP SETTING
//========================================

void EPSconnectToAP() {
  Serial.println("EPSconnectToAP() start");
  String atCommand = "AT+CWJAP=\"" + ssid + "\",\"" + password + "\"";

  if (!ESPSendAndCheckReturn(atCommand, "WIFI CONNECTED", "FAIL")) {
    Serial.println("EPSconnectToAP() start");
    // restart ESP
    return;
  }

  if (!ESPcheckReturn("WIFI GOT IP")) {
    Serial.println("EPSconnectToAP() start");
    // restart ESP
    return;
  }
  Serial.println("EPSconnectToAP() succesfull");
}

void setESPMode(String ESPmode) {
  String atCommand = "AT+CWMODE=";

  //check the mode and edit at command
  if (ESPmode == "station") {
    atCommand += "1";
  }
  if (ESPmode == "accessPoint") {
    atCommand += "2";
  }
  if (ESPmode == "both")
    atCommand += "3";

  //send at command and check for succes
  if (ESPSendAndCheckReturn(atCommand, "OK", "FAIL"))
  {
    Serial.println("setESPMode() succesfull. mode " + ESPmode);
  }
  else
  {
    Serial.println("setESPMode() fail");
  }
}

//========================================
//========================================  CONFIG ESP
//========================================

void ESPconfigure() {
  Serial.println("ESPconfigure() start setESPMode");
  setESPMode("station");
  EPSconnectToAP();
  Serial.println("ESPconfigure() end");
}

bool ESPReadyForCommand() {
  if (ESPSendAndCheckReturn("AT", "OK", "ERROR")) {
    Serial.println("ESPReadyForCommand() succesfull. EPS ready for use");
    return true;
  } else {
    Serial.println("ESPReadyForCommand() fail. No response from EPS");
  }
}

boolean startESP() {
  Serial.println("startESP() running function");
  pinMode(espChipPowerDown, OUTPUT);
  digitalWrite(espChipPowerDown, HIGH);

  if (!ESPcheckReturn("ready")) {
    Serial.println("startESP() ESP fail. No ready");
    return false;
  }

  //check if wifi is connected
  Serial.println("startESP() checking for WIFI CONNECTED");
  if (!ESPcheckReturn("WIFI CONNECTED")) {
    //if not connected configure ESP
    ESPconfigure();
  } else if (ESPcheckReturn("WIFI GOT IP")) {
    //get connect to weather api
    Serial.println("startESP() check for weather");
    return true;
  }
  else {
    //do configuration
    Serial.println("startESP() ESP NO IP do configuration");
  }
}

void joinAP () {
  String atCommand = "AT+CWJAP=";
  atCommand += '"' + ssid + "\",\"" + password + '"';
  Serial.println(atCommand);
}

void clearSerialBuffer() {
  delay(1000);
  Serial1.flush();
}

void serialBrigde() {
  // Send bytes from ESP8266 -> Teensy to Computer
  while ( Serial1.available() ) {
    Serial.write( Serial1.read() );
  }

  // Send bytes from Computer -> Teensy back to ESP8266
  while ( Serial.available() ) {
    Serial1.write( Serial.read() );
  }
}



