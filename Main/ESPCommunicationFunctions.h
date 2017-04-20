#include "ESPCommunicationHandler.h"

const int espChipPowerDown = 2;

void restartESP() {
  Serial.println("restartESP() running function");
  if (digitalRead(espChipPowerDown)) {
    Serial.println("restartESP() CHPD is HIGH, turning it to LOW");
    digitalWrite(espChipPowerDown, LOW);
    delay(3000);
  }

  digitalWrite(espChipPowerDown, HIGH);
  if (ESPcheckReturn("WIFI CONNECTED")) {
    Serial.println("restartESP() ESP is conneced to the internet");
  } else {
    Serial.println("restartESP() ESP doesn't return the wishfull response");
  }
}

bool ESPSendAndCheckReturn(String atCommand, String checkForMsg, String errorMsg) {
  String espMsg;

  Serial.println("Sending AT commnand : '" + atCommand + "'. check for msg '" + checkForMsg + "' and error Msg '" + errorMsg + "'");
  Serial1.println(atCommand);
  delay(6000);

  while (Serial1.available()) {
    delay(10);
    char inChar = (char)Serial1.read();
    espMsg += inChar;

    //  check if I see a new line
    if (inChar == '\n' || inChar == '\r') {
      // trim string so I can do the comparson
      espMsg = espMsg.trim();
      // check if the message is "OK"
      if (espMsg == checkForMsg) {
        Serial.println("ESPSendAndCheckReturn() COMPLEET ESP says : '" + checkForMsg + "'");
        delay(2500);
        return true;
      }
      else {
        if (espMsg == errorMsg) {
          Serial.println("ESPSendAndCheckReturn() ERROR ESP says" + errorMsg + checkForMsg + "'");
          delay(2500);
          return false;
        }
      }
      //Send every esp message to serial
      Serial.println("ESPSendAndCheckReturn() message : '" + espMsg + "'");
      //after reading a new line delete the whole string
      espMsg = "";
    }
  }
}

void clearSerialBuffer() {
  delay(1000);
  Serial1.flush();
}

void serialBrigde() {
  // Send bytes from ESP8266 -> Teensy to Computer
  if ( Serial1.available())
    Serial.print("serialBrigde() msg below");

  while ( Serial1.available() ) {
    Serial.write( Serial1.read() );
  }

  // Send bytes from Computer -> Teensy back to ESP8266
  while ( Serial.available() ) {
    Serial1.write( Serial.read() );
  }
}
