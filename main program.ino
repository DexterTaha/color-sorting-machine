#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Create servo and LCD objects
Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adjust 0x27 to your LCD's I2C address if different

// Define control and sensor pins
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
#define servoPin 9
#define BlueLed 11
#define GreenLed 12
#define RedLed 13

// Calibration values
int redMin = 96, redMax = 411;
int greenMin = 111, greenMax = 445;
int blueMin = 87, blueMax = 455;

// Function prototypes for reading pulse widths
int getRedPW();
int getGreenPW();
int getBluePW();

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(BlueLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(RedLed, OUTPUT);
  
  // Frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  lcd.init();  // Initialize LCD
  lcd.backlight();  // Turn on backlight
  myServo.attach(servoPin);  // Attach servo
  Serial.begin(9600);  // Start serial for debugging

  myServo.write(100);  // Initial servo position
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);

  // Read and map sensor values
  int redPW = map(getRedPW(), redMin, redMax, 255, 0);
  int greenPW = map(getGreenPW(), greenMin, greenMax, 255, 0);
  int bluePW = map(getBluePW(), blueMin, blueMax, 255, 0);
  delay(200);  // Stabilization delay after readings

  // Determine dominant color and act
  if (redPW > greenPW && redPW > bluePW) {
    Serial.println("Red");
    lcd.print("Red");
    digitalWrite(RedLed, HIGH);
    digitalWrite(GreenLed, LOW);
    digitalWrite(BlueLed, LOW);
    myServo.write(150);  // Example servo position for red
  } else if (greenPW > redPW && greenPW > bluePW) {
    Serial.println("Green");
    lcd.print("Green");
    digitalWrite(RedLed, LOW);
    digitalWrite(GreenLed, HIGH);
    digitalWrite(BlueLed, LOW);
    myServo.write(100);  // Example servo position for green
  } else if (bluePW > redPW && bluePW > greenPW) {
    Serial.println("Blue");
    lcd.print("Blue");
    digitalWrite(RedLed, LOW);
    digitalWrite(GreenLed, LOW);
    digitalWrite(BlueLed, HIGH);
    myServo.write(50);  // Example servo position for blue
  } else {
    Serial.println("No dominant color");
    lcd.print("No color");
    digitalWrite(RedLed, LOW);
    digitalWrite(GreenLed, LOW);
    digitalWrite(BlueLed, LOW);
    myServo.write(100);  // Reset servo position
  }
}

// Sensor reading functions remain unchanged
int getRedPW() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  return pulseIn(sensorOut, LOW);
}

int getGreenPW() {
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  return pulseIn(sensorOut, LOW);
}

int getBluePW() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  return pulseIn(sensorOut, LOW);
}
