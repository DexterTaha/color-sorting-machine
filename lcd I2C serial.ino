#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize the LCD connected to the I2C interface
  lcd.init();
  // Turn on the backlight
  lcd.backlight();
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  // Check if data is available to read from the serial port
  if (Serial.available() > 0) {
    // Read the incoming byte:
    String message = Serial.readStringUntil('\n');
    
    // Clear the LCD screen
    lcd.clear();
    // Set the cursor to column 0, line 0
    lcd.setCursor(0, 0);
    // Print the read value to the LCD
    lcd.print(message);
  }
}
