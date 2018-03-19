#include <SPI.h>
#include <WiFi101.h>
#include "arduino_secrets.h"

int status = WL_IDLE_STATUS;
WiFiClient client;

int pirPin = 12;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int pirVal = 0;                    // variable for reading the pin status

int switchPin = 11;
int switchVal = 0;
int switchState = LOW;

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
char server[] = "intruder.pythonanywhere.com";    // name address for Google (using DNS)

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(pirPin, INPUT);     // declare sensor as input
  pinMode(switchPin, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.setPins(8, 7, 4, 2);

  checkConnection();
}

// the loop function runs over and over again forever
void loop() {
  if (getSwitchState() == HIGH && getPirState() == HIGH) {
    sendData("1");
  }
  checkConnection();
  delay(1000);
}


void sendData(String data) {
  if (client.connect(server, 80)) {
    // Make a HTTP request:
    client.println("POST /send_data HTTP/1.1");
    client.println("Host: pythonanywhere.com");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);

  }
}

void checkConnection() {
  // check for the presence of the shield:

  if (WiFi.status() == WL_NO_SHIELD) {
    // don't continue:
    while (true);
  }

  while (status != WL_CONNECTED) {
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
}

int getSwitchState() {
  return digitalRead(switchPin);
}


int getPirState() {
  return digitalRead(pirPin);  // read input value
}

void onChangeSwitch() {
  int val = digitalRead(switchPin);
  if (val == HIGH) {
    if (switchState == LOW) {
      Serial.println("Switch to high");
      switchState = HIGH;
    }
  } else {
    if (switchState == HIGH) {
      Serial.println("Switch to low");
      switchState = LOW;
    }
  }
}

void onChangePir() {
  int val = digitalRead(pirPin);

  if (val == HIGH) {            // check if the input is HIGH
    if (pirState == LOW) {
      // we have just turned on
      onChangePirFunc(HIGH);
    }
  } else {
    if (pirState == HIGH) {
      // we have just turned off
      onChangePirFunc(LOW);
    }
  }
}

void onChangePirFunc(int newState){
  if (newState == HIGH){
    sendData("1");
  } else {
    sendData("0");
  }
  pirState = newState;
}

