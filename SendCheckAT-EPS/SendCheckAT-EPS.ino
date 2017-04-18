//**** Using a Teensy 3.2 to Connect an ESP8266 to PC USB Serial *******
//**** Teensy 3.2 RX1 = PIN0 TX1 = PIN1 to EPS8266-01*******
//**** PIN2 to CHPD on EPS8266-01*******

const int epsChipPowerDown = 2;

boolean wifiEnabled = false;
String epsMsg = "";
void setup() {

  // Setup computer to Teensy serial
  Serial.begin(115200);

  // Setup Teensy to ESP8266 serial
  Serial1.begin(115200);

  //Define eps CHPD pin
  pinMode(epsChipPowerDown, OUTPUT);
  //Turn reset pin on eps ON (functions normal)
  digitalWrite(epsChipPowerDown, HIGH);
}

void loop() {

  if (wifiEnabled == false) {
    delay(2000);
    if (checkEpsReturn("AT", "OK", "ERROR")) {
      Serial.println("Jeeeeeej");
    } else {
      Serial.println("Awwwwww");
    }
    wifiEnabled = true;
  }

  //  serialBrigde();

  //  listenToEps();

}



void listenToEps() {
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


void rebootConnect() {
  Serial.println("at eps");
  Serial1.println("AT");
}


bool checkEpsReturn(String atCommand, String checkForMsg, String errorMsg) {
  Serial.println("Sending AT commnand : '" + atCommand + "'. check for msg '" + checkForMsg + "' and error Msg '" + errorMsg + "'");
  Serial1.println(atCommand);
  delay(250);
  while (Serial1.available()) {
    delay(10);
    char inChar = (char)Serial1.read();
    epsMsg += inChar;

    //  check if I see a new line
    if (inChar == '\n' || inChar == '\r') {
      // trim string so I can do the comparson
      epsMsg + epsMsg.trim();
      // check if the message is "OK"
      if (epsMsg == checkForMsg) {
        Serial.println("COMPLEET : eps says :" + checkForMsg);
        return true;
      } else {
        if (epsMsg == errorMsg) {
          Serial.println("Error : eps says" + errorMsg);
          return false;
        }
      }

      //      after reading a new line delete the whole string
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

