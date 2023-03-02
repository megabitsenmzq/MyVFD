
const int numberPinArray[] = {15, 16, 18, 21, 12, 22, 27, 25, 32};
const int segmentPinArray[] = {14, 33, 26, 13, 19, 17, 4, 23};

// Variables will change:
int ledState = LOW;  // ledState used to set the LED


// constants won't change:
const long interval = 1000;  // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  for (int i=0;i<9;i++) {
    pinMode(numberPinArray[i], OUTPUT);
  }
  for (int i=0;i<8;i++) {
    pinMode(segmentPinArray[i], OUTPUT);
  }
  pinMode(2, OUTPUT);
}

void loop() {

  for (int i=0;i<9;i++) {
    digitalWrite(numberPinArray[i], LOW);
  }
  for (int i=0;i<8;i++) {
    digitalWrite(segmentPinArray[i], LOW);
  }

  for (int i=0;i<9;i++) {
    // delay(100);
    digitalWrite(numberPinArray[i], HIGH);
    digitalWrite(2, HIGH);
    delay(300);
    digitalWrite(numberPinArray[i], LOW);
    digitalWrite(2, LOW);
  }

  for (int i=0;i<8;i++) {
    digitalWrite(segmentPinArray[i], HIGH);
  }

  for (int i=0;i<8;i++) {
    // delay(1000);
    digitalWrite(segmentPinArray[i], LOW);
    digitalWrite(2, HIGH);
    delay(300);
    digitalWrite(segmentPinArray[i], HIGH);
    digitalWrite(2, LOW);
  }
}
