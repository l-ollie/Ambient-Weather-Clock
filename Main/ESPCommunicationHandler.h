String errorWord = "ERROR";


boolean ESPcheckReturn (String checkForMsg) {
  String espMsg;
  Serial.println();

  //Listen 6 times
  for (int i = 0; i <= 12; i++) {
    Serial.print("ESPcheckReturn() checking for " + checkForMsg + " : ");
    Serial.println(i);

    delay(500);

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
          Serial.println("ESPcheckReturn() succesful");
          return true;
        }
        else {
          if (espMsg == errorWord) {
            Serial.println("ESPcheckReturn() failed. ESP MSG" + espMsg + "'");
            return false;
          }
        }

        //Send  esp message to serial if not '\n'
        if (espMsg != "") {
          Serial.println("ESPcheckReturn() ESP MSG : '" + espMsg + "'");
        }
        //after reading a new line delete the whole string
        espMsg = "";
      }
    }
  }
  //if i check for 12 time and no wishfull result, return false
  Serial.println("ESPcheckReturn() no succes");
  return false;
}


bool ESPSendAndCheckReturn(String atCommand, String checkForMsg, String errorMsg) {
  String espMsg;
  Serial1.println(atCommand);

  //Listen 6 times
  for (int i = 0; i <= 12; i++) {
    Serial.print("ESPSendAndCheckReturn() at \t" + atCommand +  "\t check for " + checkForMsg + "\t : ");
    Serial.println(i);

    delay(1000);

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
          Serial.println("ESPSendAndCheckReturn() succesful");
          espMsg = "";
          return true;
          break;
        }
        else {
          if (espMsg == errorWord) {
            Serial.println("ESPSendAndCheckReturn() failed");
            espMsg = "";
            return false;
          }
        }

        //Send  esp message to serial if not '\n'
        if (espMsg != "") {
          Serial.println("ESPSendAndCheckReturn() ESP message '" + espMsg + "'");
        }
        //after reading a new line delete the whole string
        espMsg = "";
      }
    }
  }

  //if i check for 12 time and no wishfull result, return false\
  Serial.println("ESPSendAndCheckReturn() no succes: ");
  Serial.println("ESPSendAndCheckReturn() last command '" + atCommand + "'. check for msg '" + checkForMsg + "' and error Msg '" + errorMsg + "'\r");
  return false;
}

String epsReturnInfo() {
  String espMsg;

  // Send bytes from ESP8266 -> Teensy to Computer
  while ( Serial1.available() ) {
    delay(10);
    espMsg += Serial1.read();
  }
  return espMsg;
}

