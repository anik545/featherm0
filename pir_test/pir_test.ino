int pirPin = 12;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int pirVal = 0;                    // variable for reading the pin status

int switchPin = 11;
int switchVal = 0;
int switchState = LOW;

void setup() {
  pinMode(pirPin, INPUT);     // declare sensor as input
  pinMode(switchPin, INPUT);


  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

}

void loop() {
  onChangeSwitch();
  switchVal = getSwitchState();

  pirVal = getPirState();
  onChangePir();

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
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH8 is the voltage level)
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
    if (pirState == HIGH) {
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}


