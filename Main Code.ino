#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define relay 5

void setup() {
  // Initialize the LCD connected to the I2C interface
  lcd.init();
  // Turn on the backlight
  lcd.backlight();

  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Setup the relay pin as an OUTPUT
  pinMode(relay, OUTPUT);
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
  // Clear the LCD and print "STOP"
  lcd.clear();
  lcd.setCursor(0, 0); // Set cursor to the beginning
  lcd.print("STOP");
}

void runMotor() {
  digitalWrite(relay, HIGH);
  // Clear the LCD and print "MOVE"
  lcd.clear();
  lcd.setCursor(0, 0); // Set cursor to the beginning
  lcd.print("MOVE");
}
