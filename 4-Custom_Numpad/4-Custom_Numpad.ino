#include <Keyboard.h>
// #include <Keypad.h>

// toggle special keys with numlock
// special keys can make anything you like
bool special_keys_status = false; // default false

enum modes {
  NUMPAD, // 0
  SPECIAL, // 1
  ARROWS // 2
};

int keys_mode = NUMPAD;

int time_since_last_light = 0;
bool light_status = false;
const int BUILTIN_LED = 17;

const byte ROWS = 5; // define the number of rows on the keypad
const byte COLS = 4; // define the number of columns on the keypad

// Define the keymap
// char keys[ROWS][COLS] = {
//   {'Enter', '.', '0', '0'},
//   {'Enter', '3', '2', '1'},
//   {'+', '6', '5', '4'},
//   {'+', '9', '8', '7'},
//   {'-', '*', '/', 'num'}
// };
// char keys[ROWS][COLS] = {
//   {'KEY_KP_ENTER', 'KEY_KP_DOT'     , 'KEY_KP_0'    , 'KEY_KP_0'    },
//   {'KEY_KP_ENTER', 'KEY_KP_3'       , 'KEY_KP_2'    , 'KEY_KP_1'    },
//   {'KEY_KP_PLUS' , 'KEY_KP_6'       , 'KEY_KP_5'    , 'KEY_KP_4'    },
//   {'KEY_KP_PLUS' , 'KEY_KP_9'       , 'KEY_KP_8'    , 'KEY_KP_7'    },
//   {'KEY_KP_MINUS', 'KEY_KP_ASTERISK', 'KEY_KP_SLASH', 'KEY_NUM_LOCK'} // KEY_NUM_LOCK
// };
char keys[ROWS][COLS] = {
  {'\n', '.'     , 'KEY_KP_0'    , 'KEY_KP_0'    },
  {'\n', 'KEY_KP_3'       , 'KEY_KP_2'    , 'KEY_KP_1'    },
  {'+' , 'KEY_KP_6'       , 'KEY_KP_5'    , 'KEY_KP_4'    },
  {'+' , 'KEY_KP_9'       , 'KEY_KP_8'    , 'KEY_KP_7'    },
  {'-', '*', '/', '#'} // KEY_NUM_LOCK
};
char special_keys[ROWS][COLS] = {
  {'KEY_KP_ENTER', 'KEY_KP_DOT', 'KEY_LEFT_ALT+KEY_KP_0', 'KEY_LEFT_ALT+KEY_KP_0'},
  {'KEY_KP_ENTER', 'KEY_LEFT_ALT+KEY_KP_3', 'KEY_LEFT_ALT+KEY_KP_2', 'KEY_LEFT_ALT+KEY_KP_1'},
  {'KEY_LEFT_ALT+KEY_KP_PLUS', 'KEY_LEFT_ALT+KEY_KP_6', 'KEY_LEFT_ALT+KEY_KP_5', 'KEY_LEFT_ALT+KEY_KP_4'},
  {'KEY_LEFT_ALT+KEY_KP_PLUS', 'KEY_LEFT_ALT+KEY_KP_9', 'KEY_LEFT_ALT+KEY_KP_8', 'KEY_LEFT_ALT+KEY_KP_7'},
  {'KEY_LEFT_ALT+KEY_KP_MINUS', 'KEY_LEFT_ALT+KEY_KP_ASTERISK', 'KEY_LEFT_ALT+KEY_KP_SLASH', 'KEY_NUM_LOCK'} // KEY_NUM_LOCK
};

byte rowPins[ROWS] = {6, 5, 4, 3, 2}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 9, 8, 7}; // connect to the column pinouts of the keypad

// Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
// Keypad specialKeypad = Keypad(makeKeymap(special_keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  pinMode(BUILTIN_LED, OUTPUT); // built-in LED for special keys indicator

  // Initialize the keypad
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
  }
  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
}


void loop() {
  String key = getKey();

  if (key != "") {
    if (key == "#") { // KEY_NUM_LOCK
      // toggleKeysMode();
      Serial.println("NUMPAD");

    } else {
      // Serial.print("Mode: ");
      // Serial.println(keys_mode);

      if (keys_mode == 2) {
        Serial.print("Special Key Pressed: ");
        Serial.println(key);
        // if (specialKey.indexOf("+")) { // + means two buttons
          // Keyboard.write(specialKey); // Simulate key press
        // } else { // means a command
          // do something
        // }
        // if (specialKey)

      } else {
        Serial.print("Key Pressed: ");
        Serial.println(key);
        Keyboard.write(key.c_str()); // Simulate key press
      }
    }

    // toggleKeysModeLED();
    
    delay(1); // Adjust delay based on your needs
  }
}

bool isSpecialKeys() {
  return special_keys_status;
}

void toggleKeysMode() {
  keys_mode += 1;
  if (keys_mode > 3) { // reset
    keys_mode = 1;
  }

  // toggleKeysModeLED();
}

void toggleKeysModeLED() {
  switch (keys_mode) {
    case 2:
      if (millis() == true) {
        digitalWrite(BUILTIN_LED, HIGH); // on
        delay(200);
        digitalWrite(BUILTIN_LED, LOW); // off
        delay(200);
      }
    default:
      while (keys_mode == 1) {
        digitalWrite(BUILTIN_LED, HIGH); // on
        delay(100);
        digitalWrite(BUILTIN_LED, LOW); // off
        delay(100);
      }
  }
  // force on
  digitalWrite(BUILTIN_LED, HIGH);
}

String getKey() {
  for (int col = 0; col < COLS; col++) {
    digitalWrite(colPins[col], LOW);

    for (int row = 0; row < ROWS; row++) {
      if (digitalRead(rowPins[row]) == LOW) {
        delay(50);  // Debounce delay
        while (digitalRead(rowPins[row]) == LOW);  // Wait for the key to be released
        digitalWrite(colPins[col], HIGH);
        switch (keys_mode) {
          case 2:
            return String(special_keys[row][col]);
          default: // 1 as well
            return String(keys[row][col]);
        }
      }
    }

    digitalWrite(colPins[col], HIGH);
  }

  return "";  // Return an empty string if no key is pressed
}