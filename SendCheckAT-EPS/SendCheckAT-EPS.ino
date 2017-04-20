//**** Using a Teensy 3.2 to Connect an ESP8266 to PC USB Serial *******
//**** Teensy 3.2 RX1 = PIN0 TX1 = PIN1 to EPS8266-01*******
//**** PIN2 to CHPD on EPS8266-01*******

const int epsChipPowerDown = 2;
String error = "ERROR";
boolean StartTalk = true;
String epsMsg = "";
void setup() {

  // Setup computer to Teensy serial
  Serial.begin(115200);

  // Setup Teensy to ESP8266 serial
  Serial1.begin(115200);

  //Define eps CHPD pin
  pinMode(epsChipPowerDown, OUTPUT);
  //Turn eps ON (functions normal)
  digitalWrite(epsChipPowerDown, HIGH);
}

void loop() {

  if (StartTalk == true) {
    delay(500);
    if (EPSSendAndCheckReturn("AT", "OK", "ERROR")) {
      Serial.println("Jeeeeeej");
    } else {
      Serial.println("Awwwwww");
    }
    StartTalk = false;
  }

  //Enable only this to talk directly to EPS through the Serial monitor
  //  serialBrigde();
  //listen to "CONNECT" on the eps
  //  listenToEps();

}



void listenToConnect() {
  while (Serial1.available()) {
    delay(100);
    char inChar = (char)Serial1.read();
    epsMsg += inChar;

    //check if I see a new line
    if (inChar == '\n' || inChar == '\r') {

      //check if the message is "OK"
      if (epsMsg.trim() == "WIFI CONNECTED") {
        Serial.println("eps returned 'WIFI CONNECTED'");
        Serial.flush();
      }
      Serial.println("eps returned 'WIFI CONNECTED'");
      Serial.println("eps message :" + epsMsg);

      epsMsg = "";
    }
  }
}

void restartESP() {
  if (digitalRead(epsChipPowerDown)) {
    Serial.println("CHPD is HIGH, turning it to LOW");
    digitalWrite(epsChipPowerDown, LOW);
    delay(3000);
  }

  digitalWrite(epsChipPowerDown, HIGH);
  if (EPScheckReturn("ready")) {
    Serial.println("eps is ready");
  } else{
    Serial.println("eps doent return the wishfull response");
  }
}

boolean EPScheckReturn (String checkForMsg) {
  //Listen 6 times
  for (int i = 0; i >= 6; i++) {
    delay(1000);

    while (Serial1.available()) {
      delay(10);
      char inChar = (char)Serial1.read();
      epsMsg += inChar;

      //  check if I see a new line
      if (inChar == '\n' || inChar == '\r') {
        // trim string so I can do the comparson
        epsMsg = epsMsg.trim();
        // check if the message is "OK"
        if (epsMsg == checkForMsg) {
          Serial.println("EPScheckReturn succesful : eps says : '" + checkForMsg + "'");
          delay(250);
          return true;
        }
        else {
          if (epsMsg == error) {
            Serial.println("EPScheckReturn failed : eps says" + checkForMsg + "'");
            delay(250);
            return false;
          }
        }
        
        //Send  eps message to serial if not '\n'
        if(epsMsg != "");
        Serial.println("ESP message : '" + epsMsg + "'");
        //after reading a new line delete the whole string
        epsMsg = "";
      }
    }
  }
}

void clearSerialBuffer() {
  delay(1000);
  Serial1.flush();
}


bool EPSSendAndCheckReturn(String atCommand, String checkForMsg, String errorMsg) {
  Serial.println("Sending AT commnand : '" + atCommand + "'. check for msg '" + checkForMsg + "' and error Msg '" + errorMsg + "'");
  Serial1.println(atCommand);
  delay(6000);

  while (Serial1.available()) {
    delay(10);
    char inChar = (char)Serial1.read();
    epsMsg += inChar;

    //  check if I see a new line
    if (inChar == '\n' || inChar == '\r') {
      // trim string so I can do the comparson
      epsMsg = epsMsg.trim();
      // check if the message is "OK"
      if (epsMsg == checkForMsg) {
        Serial.println("COMPLEET : eps says : '" + checkForMsg + "'");
        delay(2500);
        return true;
      }
      else {
        if (epsMsg == errorMsg) {
          Serial.println("Error : eps says" + errorMsg + checkForMsg + "'");
          delay(2500);
          return false;
        }
      }
      //Send every eps message to serial
      Serial.println("ESP message : '" + epsMsg + "'");
      //after reading a new line delete the whole string
      epsMsg = "";
    }
  }
}

void serialBrigde() {
  // Send bytes from ESP8266 -> Teensy to Computer
  if ( Serial1.available() ) {
    Serial.write( Serial1.read() );
  }

  // Send bytes from Computer -> Teensy back to ESP8266
  if ( Serial.available() ) {
    Serial1.write( Serial.read() );
  }
}

