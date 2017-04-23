#include "ESPCommunicationHandler.h"

//Define esp CHPD pin
const int espChipPowerDown = 2;

//========================================
//========================================  CONFIG ESP
//========================================
//AT+CWMODE=1
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
  Serial.print("setESPMode() set mode command ESP :" + atCommand);
  Serial.println(atCommand);
  if (ESPSendAndCheckReturn(atCommand, "OK", "FAIL"))
  {
    Serial.println("setESPMode() succesfull. ESP set mode " + ESPmode);
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
}


bool ESPReadyForCommand() {
  if (ESPSendAndCheckReturn("AT", "OK", "ERROR")) {
    Serial.println("ESPReadyForCommand() succesfull. EPS ready for use");
    return true;
  } else {
    Serial.println("ESPReadyForCommand() fail. No response from EPS");
  }
}

void restartESP() {
  pinMode(espChipPowerDown, OUTPUT);
  digitalWrite(espChipPowerDown, LOW);
  delay(4000);
  digitalWrite(espChipPowerDown, HIGH);
}

void startESP() {
  Serial.println("startESP() running function");
  pinMode(espChipPowerDown, OUTPUT);
  digitalWrite(espChipPowerDown, HIGH);

  if (!ESPcheckReturn("ready")) {
    Serial.println("startESP() ESP fail. No ready");
    return;
  }

  //check if wifi is connected
  if (!ESPcheckReturn("WIFI CONNECTED")) {
    //do configuration
    ESPconfigure();
  }

  // check if got IP
  if (ESPcheckReturn("WIFI GOT IP")) {
    //get connect to weather api
    Serial.println("startESP() check for weather");
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

  //  AT+ CWJAP =ssid,ssid
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
