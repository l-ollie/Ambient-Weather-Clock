String errorWord = "ERROR";

boolean ESPcheckReturn (String checkForMsg) {
  String espMsg;
  //Listen 6 times
  for (int i = 0; i <= 12; i++) {
    Serial.print("ESPcheckReturn() loop : ");
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
          Serial.println("ESPcheckReturn() succesful. ESP MSG '" + checkForMsg + "'");
          return true;
        }
        else {
          if (espMsg == errorWord) {
            Serial.println("ESPcheckReturn() failed. ESP MSG" + checkForMsg + "'");
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
  return false;
}


bool ESPSendAndCheckReturn(String atCommand, String checkForMsg, String errorMsg) {
  String espMsg;
  Serial.println("Sending AT commnand : '" + atCommand + "'. check for msg '" + checkForMsg + "' and error Msg '" + errorMsg + "'");
  Serial1.println(atCommand);

  //Listen 6 times
  for (int i = 0; i <= 12; i++) {
    Serial.print("ESPSendAndCheckReturn() loop :\t");
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
          Serial.println("ESPSendAndCheckReturn() succesful. esp says : '" + checkForMsg + "'");
          return true;
        }
        else {
          if (espMsg == errorWord) {
            Serial.println("ESPSendAndCheckReturn() failed. esp says" + checkForMsg + "'");
            return false;
          }
        }

        //Send  esp message to serial if not '\n'
        if (espMsg != "") {
          Serial.println("ESPSendAndCheckReturn() ESP message : '" + espMsg + "'");
        }
        //after reading a new line delete the whole string
        espMsg = "";
      }
    }
  }
  //if i check for 12 time and no wishfull result, return false
  return false;
  Serial.println("ESPSendAndCheckReturn() no succes");
}

