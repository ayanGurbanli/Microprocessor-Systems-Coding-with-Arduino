// first code of lab 1 task
// makes onboard LED on pin 13 blink at 1Hz using regsiters
void setup() {
  // set bit 5 of data direction register b to 1 to make it an output
  DDRB |= (1 << DDB5);
}

void loop() {
  // use xor to flip the state of port b pin 5 every time the loop runs
  PORTB ^= (1 << PORTB5);
  delay(500);
}

// second code of lab 1 task
// makes onboard LED on pin13 blink at 1Hz using digitalWrite()
/*
const int ledPin = 13;
void setup() {
  // configure pin 13 as an output using the arduino library
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // set pin13 to 5v
  digitalWrite(ledPin, HIGH);
  delay(500);
  // set pin13 to 0v
  digitalWrite(ledPin, LOW);
  delay(500);
}
*/