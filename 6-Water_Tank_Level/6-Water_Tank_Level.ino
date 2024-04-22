#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>

// Define pins for the Ultrasonic sensor
#define trigPin 3
#define echoPin 2

// Create an Ultrasonic object
Ultrasonic ultrasonic(trigPin, echoPin);

// Set the LCD address (you may need to change this depending on your LCD module)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.backlight(); // Turn on the backlight
  lcd.print("Water Level:");
  Serial.begin(9600);
}

void loop() {
  // Read the distance from the Ultrasonic sensor
  float distance = ultrasonic.read();
  
  // Convert distance to water level (adjust as needed)
  int waterLevel = map(distance, 0, 200, 100, 0);

  // Display water level on Serial Monitor
  Serial.print("Water Level: ");
  Serial.println(waterLevel);

  // Display water level on LCD
  lcd.setCursor(0, 1);
  lcd.print("                ");  // Clear the previous value
  lcd.setCursor(0, 1);
  lcd.print(waterLevel);

  // Add a delay to avoid rapid updates
  delay(200);
}
