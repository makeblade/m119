/*******************Morse code*******************/
void dot() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}

void dash() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(300);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}

void display_morse() {
  dot();dot();dot();dot(); 
  delay(100);
  dot();
  delay(100);
  dot();dash();dot();dot();
  delay(100);
  dot();dash();dot();dot();
  delay(100);
  dash();dash();dash();
  delay(300);
  dot();dot();
  delay(100);
  dash();dash();
  delay(100);
  dot();dot();dash();
}
/**********************END***********************/

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  display_morse();
  delay(2000);
}
