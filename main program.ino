#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

// Define the I2C address of the LCD. Common values are 0x27 and 0x3F.
// Change it if yours is different.
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define color sensor pins

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Calibration Values
// Get these from Calibration Sketch

int redMin = 96; // Red minimum value
int redMax = 411; // Red maximum value
int greenMin = 111; // Green minimum value
int greenMax = 445; // Green maximum value
int blueMin = 87; // Blue minimum value
int blueMax = 455; // Blue maximum value

// Variables for Color Pulse Width Measurements

int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Variables for final Color values

int redValue;
int greenValue;
int blueValue;

// Variable for the Min sensing value
int minsensingvalue = 100;
void setup() {

  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Set Sensor output as input
  pinMode(sensorOut, INPUT);
  
  // Set Frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  // Initialize the LCD connected to the I2C interface
  lcd.init();
  // Turn on the backlight
  lcd.backlight();
  
  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Clear the LCD display
  lcd.clear();
  
  // Set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  
  // Read Red value
  redPW = getRedPW();
  
  // Map to value from 0-255
  redValue = map(redPW, redMin, redMax, 255, 0);
  
  // Delay to stabilize sensor
  delay(200);
  
  // Read Green value
  greenPW = getGreenPW();
  
  // Map to value from 0-255
  greenValue = map(greenPW, greenMin, greenMax, 255, 0);
  
  // Delay to stabilize sensor
  delay(200);
  
  // Read Blue value
  bluePW = getBluePW();
  
  // Map to value from 0-255
  blueValue = map(bluePW, blueMin, blueMax, 255, 0);
  
  // Delay to stabilize sensor
  delay(200);
  
  // Comparisons to determine the dominant color
  if(redValue > greenValue && redValue > blueValue && redValue >= minsensingvalue) {
    Serial.println("Red");
    lcd.print("Red");
  } else if(greenValue > redValue && greenValue > blueValue && greenValue >= minsensingvalue) {
    Serial.println("Green");
    lcd.print("Green");
  } else if(blueValue > redValue && blueValue > greenValue && blueValue >= minsensingvalue) {
    Serial.println("Blue");
    lcd.print("Blue");
  } else if(redValue < minsensingvalue && greenValue < minsensingvalue && blueValue < minsensingvalue) {
    // If all values are below 130, do nothing (no Serial print)
  } else {
    // Optional: Handle cases where two colors are equal and above 130,
    // or no single color dominates significantly.
    // For simplicity, this is left out, but you could add additional conditions here.
  }
  
}



// Function to read Red Pulse Widths
int getRedPW() {

  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;

}

// Function to read Green Pulse Widths
int getGreenPW() {

  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;

}

// Function to read Blue Pulse Widths
int getBluePW() {

  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;

}
