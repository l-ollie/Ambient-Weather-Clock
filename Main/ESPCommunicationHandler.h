String errorWord = "ERROR";

boolean ESPcheckReturn (String checkForMsg) {
  String espMsg;
  //Listen 6 times
  for (int i = 0; i <= 6; i++) {
    Serial.print("ESPcheckReturn() loop : ");
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
          Serial.println("ESPcheckReturn() succesful. esp says : '" + checkForMsg + "'");
          delay(250);
          return true;
        }
        else {
          if (espMsg == errorWord) {
            Serial.println("ESPcheckReturn() failed. esp says" + checkForMsg + "'");
            delay(250);
            return false;
          }
        }

        //Send  esp message to serial if not '\n'
                if(espMsg != ""){
        Serial.println("ESPcheckReturn() ESP message : '" + espMsg + "'");
                }
        //after reading a new line delete the whole string
        espMsg = "";
      }
    }
  }
}


