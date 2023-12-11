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

unsigned long startTime;
long existCount;

void setup() {
  startTime = millis();
  Serial.begin(9600);
  Serial.println("HELLO!");

  lcd.begin(16, 2);
  lcd.backlight(); // Turn on the backlight
  lcd.print("Welcome, Sir!");
  lcd.setCursor(0, 1);
  lcd.print("By Ayham Al Ali");
}

void loop() {
  // Read the distance from the Ultrasonic sensor
  float distance = ultrasonic.read();
  
  // Convert distance to water level (adjust as needed)
  // int waterLevel = map(distanc;
  Serial.println(distance);
  if (distance < 135) { // distance from door's left wall to door's right table ~150cm
    openDoor();
  }

  // Add a delay to avoid rapid updates
  delay(200);
}

void openDoor() {
  existCount += 1;
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;

  // Convert milliseconds to minutes
  unsigned long elapsedMinutes = elapsedTime / 60000;

  // Display text on LCD 2 lines 12 segment
  
  clearLcd();
  lcd.setCursor(0, 0);
  lcd.print("Cya Later :)");
  // EC = Exist Count, LE = Last Exit
  String line2 = "EC: ";
  line2 += String(existCount);
  line2 += ", LE: ";
  line2 += String(elapsedMinutes);

  // char lineTwo[60] = "EC: " + String(existCount) + ", LE: " + String(elapsedMinutes);
  lcd.setCursor(0, 1);
  lcd.print(line2);
  delay(2000);
  reset();
}

void clearLcd() {
  lcd.setCursor(0, 0);
  lcd.print("                "); // 16 spaces to clear the line
  lcd.setCursor(0, 1);
  lcd.print("                "); // 16 spaces to clear the line
}

void reset() {

  // lcd.begin(16, 2);
  // lcd.backlight(); // Turn on the backlight
  clearLcd();
  lcd.setCursor(0, 0);
  lcd.print("Waiting...");
  lcd.setCursor(0, 1);
  lcd.print("By Ayham Al Ali");
}