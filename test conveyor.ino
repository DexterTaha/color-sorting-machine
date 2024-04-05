#define relay 5

void setup() {
  pinMode(relay, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) { 
    char command = Serial.read(); 
    
    switch (command) {
      case '0': // Stop the motor
        stopMotor();
        break;
      case '1': // Turn motor in one direction
        runMotor();
        break;
      }
  }
}

void stopMotor() {
  digitalWrite(relay, LOW);
}
void runMotor() {
  digitalWrite(relay, HIGH);
}
