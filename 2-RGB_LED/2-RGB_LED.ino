#define RGB_RED_PIN 11
#define RGB_BLUE_PIN 10
#define RGB_GREEN_PIN 9
#define POTENTIOMETER_PIN A0

void setup()
{
  pinMode(RGB_RED_PIN, OUTPUT);
  pinMode(RGB_BLUE_PIN, OUTPUT);
  pinMode(RGB_GREEN_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{ 
  int potentiometerValue = analogRead(POTENTIOMETER_PIN);
  int rgbValue = map(potentiometerValue, 0, 1023, 0, 1535);

  int red;
  int blue;
  int green;
  
  if (rgbValue < 256) {
    red = 255;
    blue = rgbValue;
    green = 0;
  }
  else if (rgbValue < 512) {
    red = 511 - rgbValue;
    blue = 255;
    green = 0;
  }
  else if (rgbValue < 768) {
    red = 0;
    blue = 255;
    green = rgbValue - 512;
  }
  else if (rgbValue < 1024) {
    red = 0;
    blue = 1023 - rgbValue;
    green = 255;
  }
  else if (rgbValue < 1280) {
    red = rgbValue - 1024;
    blue = 0;
    green = 255;
  }
  else {
    red = 255;
    blue = 0;
    green = 1535 - rgbValue;
  }
  Serial.print("R: ");
  Serial.print(red);
  Serial.print("\nG: ");
  Serial.print(green);
  Serial.print("\nB: ");
  Serial.print(blue);
  Serial.print("\n\n");
  
  analogWrite(RGB_RED_PIN, red);
  analogWrite(RGB_BLUE_PIN, blue);
  analogWrite(RGB_GREEN_PIN, green);
}