#include <Keyboard.h>

enum Modes {
  NUMPAD, // 0
  SPECIAL, // 1
  OFF, // 2
  COUNT // this is not a mode, it's just a trick to indicate max value for modes to use getNextEnumValue() function
};

int currentMode = Modes::NUMPAD; // default is numpad mode

// int timeSinceLastLight = 0; // time since last blink
// bool light_status = true; // default is constantly on
// const int BUILTIN_LED = 17; // pro micro built-in LED pin

// RGB LED
int RGB_LED_RED_PIN = 9;
int RGB_LED_GREEN_PIN = 6;
int RGB_LED_BLUE_PIN = 5;

// WHITE LED
int WHITE_LED_PIN = 19;


const byte ROWS = 5; // define the number of rows on the keypad
const byte COLS = 4; // define the number of columns on the keypad

// Default numpad values
// map is flipped in both ways horizontally and vertically
char keys[ROWS][COLS] = {
  {'\n',    '.'           , KEY_KP_0    , KEY_KP_0    },
  {'\n',    KEY_KP_3      , KEY_KP_2    , KEY_KP_1    },
  {'+' ,    KEY_KP_6      , KEY_KP_5    , KEY_KP_4    },
  {'+' ,    KEY_KP_9      , KEY_KP_8    , KEY_KP_7    },
  {'-' ,    '*'           , '/'         , '#'           } // KEY_NUM_LOCK
};

// Special keys map
// empty keys (\0) are yet to be assigned, as of now I don't have a use for them, but later I will
// using '\0' as c++ won't accept empty characters like '' as that's considered escaping character '
// \0 is null value
char special_keys[ROWS][COLS] = {
  {'\0'     , '\0'     , '\0'     , '\0'},
  {'\0'     , KEY_F15, KEY_F14, KEY_F13 },
  {'\0     ', KEY_F18, KEY_F17, KEY_F16 },
  {'\0     ', KEY_F21, KEY_F20, KEY_F19 },
  {KEY_F24  , KEY_F23, KEY_F22, '#'     } // KEY_NUM_LOCK
};


// Special keys map
// empty keys (\0) are yet to be assigned, as of now I don't have a use for them, but later I will
// using '\0' as c++ won't accept empty characters like '' as that's considered escaping character '
// \0 is null value
char off_keys[ROWS][COLS] = {
  { '\0', '\0', '\0', '\0' },
  { '\0', '\0', '\0', '\0' },
  { '\0', '\0', '\0', '\0' },
  { '\0', '\0', '\0', '\0' },
  { '\0', '\0', '\0', '#'  }  // KEY_NUM_LOCK
};

// row/column pins 
byte rowPins[ROWS] = {18, 14, 4, 15, 2}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 16, 8, 7}; // connect to the column pinouts of the keypad

// setup funs once at device connection, for setting up the device configuration
void setup() {
  Serial.begin(9600);

  // begin the keyboard library
  Keyboard.begin();
  // pinMode(BUILTIN_LED, OUTPUT); // built-in LED for special keys indicator
  // digitalWrite(BUILTIN_LED, HIGH); // turn on by default

  // LED Setup
  pinMode(RGB_LED_RED_PIN, OUTPUT);
  pinMode(RGB_LED_GREEN_PIN, OUTPUT);
  pinMode(RGB_LED_BLUE_PIN, OUTPUT);
  pinMode(WHITE_LED_PIN, OUTPUT);

  digitalWrite(WHITE_LED_PIN, HIGH); // turn on WHITE LED by default

  // Initialize the keypad
  for (int i = 0; i < ROWS; i++) { // rows
    pinMode(rowPins[i], INPUT_PULLUP);
  }
  for (int i = 0; i < COLS; i++) { // columns
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }

  updateLighting();
  
}

// loop keeps re-running as fast as possible
void loop() {
  // key key value pressed from the current mode map
  String key = getKey();

  if (key != "" || key != '\0') { // make sure a key is pressed
    if (key == "#") { // KEY_NUM_LOCK, toggle between modes
      toggleKeysMode();
    } else {
      Keyboard.write(key.c_str()[0]); // Simulate key press -- convert string to list of characters and grab the first character
    }
    
    delay(1); // delay in ms to avoid bugs such as multiple prints for a single press, must not be very high otherwise fast typing won't work
  }
}

// Get key pressed
String getKey() {
  for (int col = 0; col < COLS; col++) {
    digitalWrite(colPins[col], LOW);

    for (int row = 0; row < ROWS; row++) {
      if (digitalRead(rowPins[row]) == LOW) {
        delay(50);  // Debounce delay
        while (digitalRead(rowPins[row]) == LOW);  // Wait for the key to be released
        digitalWrite(colPins[col], HIGH);
        // choose key based on mode
        switch (currentMode) {
          case Modes::SPECIAL:
            return String(special_keys[row][col]);
          case Modes::OFF:
            return String(off_keys[row][col]);
          case Modes::NUMPAD:
            return String(keys[row][col]);
        }
      }
    }

    digitalWrite(colPins[col], HIGH);
  }

  return "";  // Return an empty string if no key is pressed
}

// general function to convert enum to integer and get next value by converting new integer to enum
template<typename T>
T getNextEnumValue(T currentEnum, int maxCount) {
    int nextValue = static_cast<int>(currentEnum) + 1;

    // Check if the next value exceeds the maximum enum value
    if (nextValue >= static_cast<int>(maxCount)) {
        // If so, wrap around to the first enum value
        nextValue = 0;
    }

    return static_cast<T>(nextValue);
}

// toggle modes
void toggleKeysMode() {
  currentMode = getNextEnumValue(currentMode, Modes::COUNT);
  updateLighting();
}

// toggle/check LED based on mode
void updateLighting() {
  switch (currentMode) {
    case Modes::NUMPAD:
      setRGBColor(0, 255, 42); // green
      break;
    case Modes::SPECIAL:
      setRGBColor(157, 0, 255); // purple
      break;
    case Modes::OFF:
      setRGBColor(0, 0, 0); // black - off
      break;
  }
}

// RGB LED Control
void setRGBColor(int red, int green, int blue) {
  analogWrite(RGB_LED_RED_PIN, red);
  analogWrite(RGB_LED_GREEN_PIN, green);
  analogWrite(RGB_LED_BLUE_PIN, blue);
}