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
    atCommand = "AT+CWMODE=" + 1;
  } else {
    if (ESPmode == "accessPoint") {
      atCommand = "AT+CWMODE=" + 2;
    } else {
      if (ESPmode == "both")
        atCommand = "AT+CWMODE=" + 3;
    }

    //send at command and check for succes
    if (ESPSendAndCheckReturn(atCommand, "OK", "FAIL"))
    {
      Serial.println("setESPMode() succesfull. ESP set mode " + ESPmode);
    }
    else
    {
      Serial.println("setESPMode() fail");
    }
  }
}


//========================================
//========================================  CONFIG ESP
//========================================

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

  if (ESPcheckReturn("ready")) {

    // after cheking "ready" check if connected
    if (ESPcheckReturn("WIFI CONNECTED")) {

      //after ckeck "WIFI CONNECTED" check if got IP
      if (ESPcheckReturn("WIFI GOT IP"))      {
        //get connect to weather api
      }
      //if no IP hase recieved configure ESP
      else {
        //do configuration
      }

    } else
    {
      //do configuration
    }
    Serial.println("startESP() ESP no WIFI CONNECTED");
  }

  //if no "ready" return
  else {
    Serial.println("startESP() ESP fail. No ready");
  }
}


  void ESPconfigure() {
    setESPMode("station");
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
